#pragma once
#include <algorithm>
#include <cassert>
#include <compare>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include "convolution/ntt.hpp"

/// @brief 多倍長整数
/// @details 内部は基数 BASE = 10^6 のリトルエンディアン配列で保持する。
///          各桁は [0, BASE) の非負整数で、最上位桁 (末尾) が 0 となる
///          冗長表現を持たない (値 0 は {0} のみ)。符号は sign が表す
///          (負なら true)。ゼロは常に sign == false に正規化される。
/// @see https://qiita.com/square1001/items/1aa12e04934b6e749962
/// @see http://yamatyuu.net/computer/program/long/div/index.html
struct BigInt {
    /// 1 桁が表す基数。10 進 6 桁。
    static constexpr int BASE = 1'000'000;
    /// BASE の 10 進桁数。入出力の整形に使う。
    static constexpr int BASE_DIGITS = 6;
    /// 除数がこの桁数以下なら Burnikel-Ziegler 再帰をやめて古典除算に切り替える。
    static constexpr int BZ_THRESHOLD = 64;
    /// 乗算で 2 素数 NTT (convolution_ll2) を使える最大畳み込み長。
    /// 係数積は高々 (BASE-1)^2 * len なので、これが MOD1*MOD3 (約 3.5e17) 未満となる
    /// len の上限。これを超える巨大乗算のみ 3 素数版 (convolution_ll) へ落とす。
    static constexpr int MUL_2PRIME_MAX_LEN = 354659;

    BigInt() : data(1, 0), sign(false) {}
    explicit BigInt(std::int64_t x) : data(), sign(x < 0) {
        // INT64_MIN を -x で反転すると UB になるため、符号なしで絶対値を取る。
        std::uint64_t u = sign ? -(std::uint64_t)x : (std::uint64_t)x;
        do {
            data.emplace_back(int(u % BASE));
            u /= BASE;
        } while (u);
        normalize();
    }
    explicit BigInt(const std::string &s) : data(), sign(false) {
        int start = 0;
        if (!s.empty() && (s[0] == '-' || s[0] == '+')) {
            sign = (s[0] == '-');
            start = 1;
        }
        assert((int)s.size() > start && "BigInt: empty numeric string");
        // 下位 BASE_DIGITS 桁ずつまとめて 1 桁に詰める。
        for (int i = (int)s.size(); i > start; i -= BASE_DIGITS) {
            int from = std::max(start, i - BASE_DIGITS);
            int x = 0;
            for (int j = from; j < i; ++j) {
                assert('0' <= s[j] && s[j] <= '9' && "BigInt: non-digit character");
                x = x * 10 + (s[j] - '0');
            }
            data.emplace_back(x);
        }
        normalize();
    }
    explicit BigInt(const std::vector<int> &v, bool flag = false) : data(v), sign(flag) {
        if (data.empty()) data.emplace_back(0);
        carry();
        normalize();
    }

    BigInt &operator+=(const BigInt &rhs) {
        if (sign == rhs.sign) {
            add(data, rhs.data);
        } else if (abs_less_or_eq_data(data, rhs.data)) {
            // |this| <= |rhs| なので符号は rhs に従う。
            std::vector<int> t = rhs.data;
            sub(t, data);
            data = std::move(t);
            sign = rhs.sign;
        } else {
            sub(data, rhs.data);
        }
        normalize();
        return *this;
    }
    BigInt &operator-=(const BigInt &rhs) { return *this += -rhs; }
    BigInt &operator*=(const BigInt &rhs) {
        sign ^= rhs.sign;
        mul(data, rhs.data);
        normalize();
        return *this;
    }
    BigInt &operator*=(std::int64_t rhs) { return *this *= BigInt(rhs); }
    BigInt &operator/=(const BigInt &rhs) {
        auto [q, r] = divmod(*this, rhs);
        return *this = q;
    }
    BigInt &operator%=(const BigInt &rhs) {
        auto [q, r] = divmod(*this, rhs);
        return *this = r;
    }
    BigInt &operator/=(std::int64_t rhs) { return *this /= BigInt(rhs); }
    BigInt &operator%=(std::int64_t rhs) { return *this %= BigInt(rhs); }

    BigInt operator-() const {
        BigInt res = *this;
        if (!res.is_zero()) res.sign = !res.sign;
        return res;
    }
    BigInt operator+(const BigInt &rhs) const { return BigInt(*this) += rhs; }
    BigInt operator-(const BigInt &rhs) const { return BigInt(*this) -= rhs; }
    BigInt operator*(const BigInt &rhs) const { return BigInt(*this) *= rhs; }
    BigInt operator*(std::int64_t rhs) const { return BigInt(*this) *= rhs; }
    BigInt operator/(const BigInt &rhs) const { return BigInt(*this) /= rhs; }
    BigInt operator%(const BigInt &rhs) const { return BigInt(*this) %= rhs; }

    bool operator==(const BigInt &rhs) const { return sign == rhs.sign && data == rhs.data; }
    std::strong_ordering operator<=>(const BigInt &rhs) const {
        if (sign != rhs.sign) return sign ? std::strong_ordering::less : std::strong_ordering::greater;
        if (data == rhs.data) return std::strong_ordering::equal;
        // 同符号なら絶対値比較。負同士は大小が反転する。
        bool less = sign ? abs_less_data(rhs.data, data) : abs_less_data(data, rhs.data);
        return less ? std::strong_ordering::less : std::strong_ordering::greater;
    }

    friend std::istream &operator>>(std::istream &is, BigInt &rhs) {
        std::string s;
        is >> s;
        rhs = BigInt(s);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const BigInt &rhs) { return os << rhs.to_string(); }

    std::string to_string() const {
        std::string s;
        if (sign) s.push_back('-');
        s += std::to_string(data.back());
        // 最上位以外は BASE_DIGITS 桁にゼロ埋めする。
        for (int i = size() - 2; i >= 0; --i) {
            std::string t = std::to_string(data[i]);
            s.append(BASE_DIGITS - (int)t.size(), '0');
            s += t;
        }
        return s;
    }

    int size() const { return (int)data.size(); }
    bool is_zero() const { return size() == 1 && data[0] == 0; }

    BigInt abs() const {
        BigInt res = *this;
        res.sign = false;
        return res;
    }
    /// |*this| < |rhs| を返す。
    bool abs_less(const BigInt &rhs) const { return abs_less_data(data, rhs.data); }

    /// 商と余りを同時に返す ({*this / rhs, *this % rhs})。除算を 1 回で済ませられる。
    /// 余りは被除数 (*this) と同符号 (truncation 方向、operator% と同じ規約)。
    std::pair<BigInt, BigInt> div_mod(const BigInt &rhs) const { return divmod(*this, rhs); }
    std::pair<BigInt, BigInt> div_mod(std::int64_t rhs) const { return divmod(*this, BigInt(rhs)); }

  private:
    std::vector<int> data;
    bool sign;

    /// 絶対値 (data 同士) の < 比較。
    static bool abs_less_data(const std::vector<int> &a, const std::vector<int> &b) {
        if (a.size() != b.size()) return a.size() < b.size();
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            if (a[i] != b[i]) return a[i] < b[i];
        }
        return false;
    }
    static bool abs_less_or_eq_data(const std::vector<int> &a, const std::vector<int> &b) {
        return !abs_less_data(b, a);
    }

    /// a += b (絶対値同士の加算)。
    static void add(std::vector<int> &a, const std::vector<int> &b) {
        if (a.size() < b.size()) a.resize(b.size(), 0);
        int carry = 0;
        for (int i = 0; i < (int)a.size(); ++i) {
            a[i] += carry + (i < (int)b.size() ? b[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
        if (carry) a.emplace_back(1);
    }
    /// a -= b (a >= b >= 0 を前提とした絶対値の減算)。
    static void sub(std::vector<int> &a, const std::vector<int> &b) {
        int borrow = 0;
        for (int i = 0; i < (int)a.size(); ++i) {
            a[i] -= borrow + (i < (int)b.size() ? b[i] : 0);
            borrow = a[i] < 0;
            if (borrow) a[i] += BASE;
        }
        trim(a);
    }
    /// a *= b (絶対値同士の乗算)。畳み込みは真値を返す convolution を使う。
    /// 畳み込み長が MUL_2PRIME_MAX_LEN 以下なら 2 素数版 (convolution_ll2) で十分速く、
    /// それを超える巨大乗算のみ 3 素数版 (convolution_ll) へフォールバックする。
    static void mul(std::vector<int> &a, const std::vector<int> &b) {
        if ((a.size() == 1 && a[0] == 0) || (b.size() == 1 && b[0] == 0)) {
            a.assign(1, 0);
            return;
        }
        std::vector<std::int64_t> x(a.begin(), a.end()), y(b.begin(), b.end());
        std::vector<std::int64_t> c =
            (x.size() + y.size() <= MUL_2PRIME_MAX_LEN) ? convolution_ll2(x, y) : convolution_ll(x, y);
        std::int64_t carry = 0;
        a.assign(c.size() + 1, 0);
        for (int i = 0; i < (int)c.size(); ++i) {
            std::int64_t cur = c[i] + carry;
            a[i] = int(cur % BASE);
            carry = cur / BASE;
        }
        a[c.size()] = int(carry);
        trim(a);
    }

    /// data の各桁を [0, BASE) に繰り上げ・繰り下げ整形する。
    /// コンストラクタが冗長な (または範囲外の) 桁を受け取ったときに使う。
    void carry() {
        std::int64_t c = 0;
        for (int i = 0; i < (int)data.size(); ++i) {
            std::int64_t cur = (std::int64_t)data[i] + c;
            int r = int(cur % BASE);
            c = cur / BASE;
            if (r < 0) {
                r += BASE;
                --c;
            }
            data[i] = r;
        }
        while (c > 0) {
            data.emplace_back(int(c % BASE));
            c /= BASE;
        }
    }

    /// 最上位の余分な 0 桁を削る (最低 1 桁は残す)。
    static void trim(std::vector<int> &a) {
        while (a.size() > 1 && a.back() == 0) a.pop_back();
    }
    /// trim に加えてゼロの符号を正す。
    void normalize() {
        trim(data);
        if (is_zero()) sign = false;
    }

    /// a の [from, from+len) 桁を取り出す (範囲外は 0 埋め)。結果は trim 済み。
    static std::vector<int> slice(const std::vector<int> &a, int from, int len) {
        if (len <= 0) return {0};
        std::vector<int> r(len, 0);
        for (int i = 0; i < len; ++i) {
            int idx = from + i;
            if (0 <= idx && idx < (int)a.size()) r[i] = a[idx];
        }
        trim(r);
        return r;
    }
    /// low + high * BASE^k を返す。low が k 桁を超える分は high 側へ正しく繰り上がる。
    static std::vector<int> combine(const std::vector<int> &low, const std::vector<int> &high, int k) {
        // r = high << k に low を加算する (low の桁あふれも add が処理する)。
        std::vector<int> r;
        if (high.size() == 1 && high[0] == 0) {
            r.assign(1, 0);
        } else {
            r.assign(k, 0);
            r.insert(r.end(), high.begin(), high.end());
        }
        add(r, low);
        trim(r);
        return r;
    }

    /// 古典筆算除算 (Knuth Algorithm D)。(商, 余り) を絶対値で返す。
    /// lhs >= rhs > 0 を前提とする (呼び出し側で短絡済み)。
    static std::pair<std::vector<int>, std::vector<int>> divmod_classic(const std::vector<int> &lhs,
                                                                        const std::vector<int> &rhs) {
        // 正規化: 最上位桁が BASE/2 以上になるよう両者を同じ係数倍する。
        std::vector<int> u = lhs, v = rhs;
        int norm = BASE / (v.back() + 1);
        mul(u, std::vector<int>{norm});
        mul(v, std::vector<int>{norm});
        int n = (int)v.size(), m = (int)u.size() - n;
        if (m < 0) return {{0}, lhs};  // |lhs| < |rhs|
        u.resize(u.size() + 1, 0);
        std::vector<int> quot(m + 1, 0);
        for (int j = m; j >= 0; --j) {
            // 上位 2 桁から商の候補を見積もる。
            std::int64_t num = (std::int64_t)u[j + n] * BASE + u[j + n - 1];
            std::int64_t qhat = num / v[n - 1];
            std::int64_t rhat = num % v[n - 1];
            while (qhat >= BASE || (n >= 2 && qhat * v[n - 2] > rhat * BASE + u[j + n - 2])) {
                --qhat;
                rhat += v[n - 1];
                if (rhat >= BASE) break;
            }
            // u[j..j+n] -= qhat * v
            std::int64_t borrow = 0, carry = 0;
            for (int i = 0; i < n; ++i) {
                carry += qhat * v[i];
                std::int64_t sub_digit = (std::int64_t)u[j + i] - borrow - (carry % BASE);
                carry /= BASE;
                borrow = 0;
                if (sub_digit < 0) {
                    sub_digit += BASE;
                    borrow = 1;
                }
                u[j + i] = int(sub_digit);
            }
            std::int64_t top = (std::int64_t)u[j + n] - borrow - carry;
            if (top < 0) {
                // 見積もりが 1 大きすぎた場合の補正: v を 1 回足し戻す。
                --qhat;
                std::int64_t add_carry = 0;
                for (int i = 0; i < n; ++i) {
                    add_carry += (std::int64_t)u[j + i] + v[i];
                    u[j + i] = int(add_carry % BASE);
                    add_carry /= BASE;
                }
                top += add_carry;
            }
            u[j + n] = int(top);
            quot[j] = int(qhat);
        }
        trim(quot);
        // 余り = 正規化後の u を norm で割って戻す。
        trim(u);
        div_small(u, norm);
        return {quot, u};
    }

    /// (商, 余り) を返す。余りは被除数と同符号 (truncation 方向)。
    static std::pair<BigInt, BigInt> divmod(const BigInt &lhs, const BigInt &rhs) {
        assert(!rhs.is_zero() && "BigInt: division by zero");
        if (abs_less_data(lhs.data, rhs.data)) return {BigInt(), lhs};

        std::vector<int> q, r;
        if ((int)rhs.data.size() == 1) {
            // 1 桁除数は O(n) のスカラ除算で済ませる。
            q = lhs.data;
            r = {div_small(q, rhs.data[0])};
        } else if ((int)rhs.data.size() <= BZ_THRESHOLD) {
            // 除数が小さいときは古典除算の方が速い。
            std::tie(q, r) = divmod_classic(lhs.data, rhs.data);
        } else {
            std::tie(q, r) = divmod_bz(lhs.data, rhs.data);
        }
        BigInt qq(q, lhs.sign ^ rhs.sign);
        BigInt rr(r, lhs.sign);
        return {qq, rr};
    }

    /// Burnikel-Ziegler の再帰除算。lhs >= rhs > 0、|rhs| > BZ_THRESHOLD を前提とする。
    /// 除数をブロック幅 blk (再帰の各段で偶数長になる) ちょうどに正規化し、被除数を
    /// blk 桁ブロックに分けて 2n/1n 除算を繰り返す。
    static std::pair<std::vector<int>, std::vector<int>> divmod_bz(const std::vector<int> &lhs,
                                                                   const std::vector<int> &rhs) {
        int n = (int)rhs.size();
        // ブロック幅 blk: 各再帰段で偶数長を保つため BZ_THRESHOLD*2^k 以上へ切り上げる。
        int m = 1;
        while (m * BZ_THRESHOLD < n) m <<= 1;
        int blk = ((n + m - 1) / m) * m;
        // 正規化 (最上位桁 >= BASE/2) と低位シフトを 1 係数 sh = norm * BASE^(blk-n) に
        // まとめて両者へ掛ける。これで b はちょうど blk 桁・最上位 >= BASE/2 になる。
        int norm = BASE / (rhs.back() + 1);
        std::vector<int> sh(blk - n + 1, 0);
        sh[blk - n] = norm;
        std::vector<int> a = lhs, b = rhs;
        mul(a, sh);
        mul(b, sh);
        b.resize(blk, 0);  // mul で末尾 0 が落ちた場合に備えて厳密に blk 桁へ

        // 被除数を上位から blk 桁ブロックに分け、各ブロックで 2n/1n 除算する。
        // 最上位ブロックが必ず b 未満になるよう、桁数が blk の倍数のときは 1 ブロック多く取る。
        int t = (int)a.size() / blk + 1;
        if (t < 2) t = 2;
        std::vector<int> rem = slice(a, (t - 1) * blk, blk);  // 初期の上位ブロック (< b)
        std::vector<int> q;                                   // 商を上位ブロックから連結
        for (int i = t - 2; i >= 0; --i) {
            // cur = rem * BASE^blk + a[i*blk .. i*blk+blk) (高々 2*blk 桁) を b で割る。
            std::vector<int> cur = combine(slice(a, i * blk, blk), rem, blk);
            auto [qi, ri] = div_2n_1n(cur, b);
            q = combine(qi, q, blk);  // q = qi + q * BASE^blk
            rem = ri;
        }
        trim(q);
        // 余りは sh = norm * BASE^(blk-n) を戻す。低位 blk-n 桁は 0 なので削って norm で割る。
        rem.erase(rem.begin(), rem.begin() + std::min((int)rem.size(), blk - n));
        if (rem.empty()) rem.assign(1, 0);
        div_small(rem, norm);
        return {q, rem};
    }

    /// a (高々 2n 桁) を b (n 桁、正規化済み・n は偶数) で割る。商 < BASE^n を前提。
    static std::pair<std::vector<int>, std::vector<int>> div_2n_1n(const std::vector<int> &a,
                                                                   const std::vector<int> &b) {
        int n = (int)b.size();
        if (n <= BZ_THRESHOLD || (int)a.size() <= n) return divmod_classic(a, b);
        // 上位・下位 n/2 桁に分け、div_3n_2n を 2 回適用する (n は偶数)。
        int s = n / 2;
        std::vector<int> a_lo = slice(a, 0, s);                  // 下位 s 桁
        std::vector<int> a_hi = slice(a, s, (int)a.size() - s);  // 上位
        auto [q1, r1] = div_3n_2n(a_hi, b, s);
        std::vector<int> mid = combine(a_lo, r1, s);  // r1*BASE^s + a_lo
        auto [q2, r2] = div_3n_2n(mid, b, s);
        std::vector<int> q = combine(q2, q1, s);  // q1*BASE^s + q2
        return {q, r2};
    }

    /// a (高々 3s 桁) を b (= 2s 桁) で割る。商 < BASE^s を前提とする。
    /// b = b1*BASE^s + b2 と分け、a の上位 2s 桁を b1 で見積もり b2 の積で補正する。
    static std::pair<std::vector<int>, std::vector<int>> div_3n_2n(const std::vector<int> &a, const std::vector<int> &b,
                                                                   int s) {
        std::vector<int> b2 = slice(b, 0, s);  // 下位 s 桁
        std::vector<int> b1 = slice(b, s, s);  // 上位 s 桁
        // a = a12 * BASE^s + a3 (a3 は下位 s 桁、a12 は上位 2s 桁)。
        std::vector<int> a3 = slice(a, 0, s);
        std::vector<int> a12 = slice(a, s, (int)a.size() - s);
        std::vector<int> qhat, r1;
        // a12 の上位 s 桁が b1 以上なら商は BASE^s に達する。div_2n_1n は商 < BASE^s を
        // 前提とするので、その境界では qhat = BASE^s - 1 に固定し r1 = a12 - qhat*b1 とする。
        if (!abs_less_data(slice(a12, s, s), b1)) {
            qhat.assign(s, BASE - 1);  // BASE^s - 1
            trim(qhat);
            r1 = a12;
            std::vector<int> qb1 = qhat;
            mul(qb1, b1);
            sub(r1, qb1);  // r1 = a12 - (BASE^s - 1)*b1 (>= 0)
        } else {
            std::tie(qhat, r1) = div_2n_1n(a12, b1);
        }
        // rr = r1 * BASE^s + a3 (D を引く前の候補余り)、d = qhat * b2。
        std::vector<int> rr = combine(a3, r1, s);
        std::vector<int> d = qhat;
        mul(d, b2);
        // r = rr - d。負 (rr < d) の間 qhat を減らし b (= b1*BASE^s + b2) を足し戻す (高々 2 回)。
        while (abs_less_data(rr, d)) {
            sub(qhat, std::vector<int>{1});
            add(rr, b);
        }
        sub(rr, d);
        std::vector<int> r = rr;
        trim(qhat);
        return {qhat, r};
    }

    /// data /= k (0 < k < BASE のスカラ除算、絶対値)。余りを返す。
    static int div_small(std::vector<int> &data, int k) {
        std::int64_t rem = 0;
        for (int i = (int)data.size() - 1; i >= 0; --i) {
            std::int64_t cur = rem * BASE + data[i];
            data[i] = int(cur / k);
            rem = cur % k;
        }
        trim(data);
        return int(rem);
    }
};
