#pragma once
#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

/// @brief 既約分数 (Stern-Brocot 木のノード)
///
/// 正の有理数を p/q で表す。0 は 0/1、+∞ は 1/0 として扱える。
/// 比較は __int128 でクロス積を取りオーバーフローを避ける。
struct sbt_fraction {
    std::int64_t p, q;

    constexpr sbt_fraction() : p(0), q(1) {}
    constexpr sbt_fraction(std::int64_t p, std::int64_t q) : p(p), q(q) {}

    friend constexpr bool operator==(const sbt_fraction &a, const sbt_fraction &b) { return a.p == b.p && a.q == b.q; }
    friend constexpr auto operator<=>(const sbt_fraction &a, const sbt_fraction &b) {
        return (__int128)a.p * b.q <=> (__int128)b.p * a.q;
    }
};

/// @brief Stern-Brocot 木
///
/// 正の有理数を既約分数 p/q として木のノードと同一視する。根は 1/1。
/// 各ノードを子孫が成す開区間の左端 lo・右端 hi で保持し、メディアントが
/// そのノードの値になる。左の子へ進む移動を 'L'、右の子へ進む移動を 'R' とし、
/// パスは連長圧縮 (各要素は (移動文字, 連続回数)) で表す。
struct stern_brocot_tree {
    using fraction = sbt_fraction;
    using path = std::vector<std::pair<char, std::int64_t>>;

    // 根 1/1。区間は (0/1, 1/0)。
    constexpr stern_brocot_tree() : lo(0, 1), hi(1, 0) {}
    constexpr stern_brocot_tree(fraction lo, fraction hi) : lo(lo), hi(hi) {}

    // p/q を含むノードを構成する (区間が p/q を含むまで降りる)。
    static stern_brocot_tree from_fraction(fraction f) { return from_path(encode(f)); }

    // パスを根から辿った先のノード。
    static stern_brocot_tree from_path(const path &pth) {
        stern_brocot_tree t;
        for (auto [c, k] : pth) t.descend(c, k);
        return t;
    }

    // このノードが表す既約分数 (メディアント)。
    constexpr fraction value() const { return {lo.p + hi.p, lo.q + hi.q}; }

    // 子孫が成す開区間 (左端, 右端)。0 は 0/1、+∞ は 1/0。
    constexpr std::pair<fraction, fraction> range() const { return {lo, hi}; }

    constexpr bool is_root() const { return lo.p == 0 && lo.q == 1 && hi.p == 1 && hi.q == 0; }

    // 左/右の子へ k 回 (既定 1 回) 降りた子孫。
    constexpr stern_brocot_tree left(std::int64_t k = 1) const {
        stern_brocot_tree t = *this;
        t.descend('L', k);
        return t;
    }
    constexpr stern_brocot_tree right(std::int64_t k = 1) const {
        stern_brocot_tree t = *this;
        t.descend('R', k);
        return t;
    }

    // 根からの深さ (移動回数の総和)。根は 0。
    std::int64_t depth() const {
        std::int64_t res = 0;
        for (auto [c, n] : path_from_root()) res += n;
        return res;
    }

    // 根からこのノードまでのパス (連長圧縮)。
    path path_from_root() const { return encode(value()); }

    // --- 静的ユーティリティ (有理数を直接操作) ---

    // 1/1 から f までのパスを連長圧縮で求める。1/1 のとき空。
    static path encode(fraction f) {
        std::int64_t a = f.p, b = f.q;
        path res;
        while (a != 1 || b != 1) {
            if (a > b) {
                std::int64_t k = (a - 1) / b;
                res.emplace_back('R', k);
                a -= k * b;
            } else {
                std::int64_t k = (b - 1) / a;
                res.emplace_back('L', k);
                b -= k * a;
            }
        }
        return res;
    }

    // パスが指す既約分数。
    static fraction decode(const path &pth) { return from_path(pth).value(); }

    // a/b と c/d の最近共通祖先。
    static fraction lca(fraction f, fraction g) {
        path p = encode(f), q = encode(g), res;
        for (std::size_t i = 0; i < std::min(p.size(), q.size()); ++i) {
            auto [c1, n1] = p[i];
            auto [c2, n2] = q[i];
            if (c1 != c2) break;
            res.emplace_back(c1, std::min(n1, n2));
            if (n1 != n2) break;
        }
        return decode(res);
    }

    // f の祖先のうち深さ k のもの。存在しなければ無効値 {0, 0}。
    static fraction ancestor(std::int64_t k, fraction f) {
        path res;
        for (auto [c, n] : encode(f)) {
            if (k <= n) {
                res.emplace_back(c, k);
                return decode(res);
            }
            res.emplace_back(c, n);
            k -= n;
        }
        return {0, 0};
    }

    // 目標有理数 target (= p/q, 既約でなくてよい。0/1 や 1/0 も可) に最も近い、
    // 分母が max_denominator 以下の既約分数を返す。距離が等しいときは値が小さい方。
    // SBT を target に向かって降りる過程で、各方向への連続ステップ数を
    // 「target を越えない最大回数」と「分母制約を超えない最大回数」の小さい方として
    // 閉じた式で一括計算するため O(log) で求まる。比較は __int128。
    static fraction nearest(fraction target, std::int64_t max_denominator) {
        using i128 = __int128;
        const i128 R = target.p, D = target.q, N = max_denominator;
        // target との符号付きクロス差 p*D - R*q (0 で一致)。
        auto diff = [&](i128 p, i128 q) { return p * D - R * q; };

        stern_brocot_tree t;
        while (true) {
            // 境界がちょうど target なら距離 0 で確定 (分母 <= N なら採用)。
            if (t.lo.q != 0 && diff(t.lo.p, t.lo.q) == 0 && t.lo.q <= N) return t.lo;
            if (t.hi.q != 0 && diff(t.hi.p, t.hi.q) == 0 && t.hi.q <= N) return t.hi;

            fraction m = t.value();
            i128 dm = diff(m.p, m.q);
            if (dm == 0) {
                if (m.q <= N) return m;
                break;  // メディアントは target だが分母超過 -> 境界で判定
            }
            if (dm < 0) {
                // メディアント < target: 右へ lo += k*hi。
                // k <= (R*lo.q - lo.p*D) / (hi.p*D - R*hi.q) で target を越えない。
                i128 num = -diff(t.lo.p, t.lo.q);  // > 0
                i128 den = diff(t.hi.p, t.hi.q);   // > 0 (hi > target)
                i128 kr = num / den;
                // hi.q == 0 (hi が +∞) のときは分母制約がかからない。
                bool denom_free = (t.hi.q == 0);
                i128 kn = denom_free ? kr : (N - t.lo.q) / t.hi.q;  // 分母 <= N
                i128 k = denom_free ? kr : std::min(kr, kn);
                if (k <= 0) break;
                t.lo = {t.lo.p + (std::int64_t)k * t.hi.p, t.lo.q + (std::int64_t)k * t.hi.q};
                if (!denom_free && k < kr) break;  // 分母制約で目標まで進めず終了
            } else {
                // メディアント > target: 左へ hi += k*lo。
                i128 num = diff(t.hi.p, t.hi.q);   // > 0
                i128 den = -diff(t.lo.p, t.lo.q);  // > 0 (lo < target)
                i128 kr = num / den;
                // lo.q == 0 はありえない (lo は常に有限) が、対称性のため同様に扱う。
                bool denom_free = (t.lo.q == 0);
                i128 kn = denom_free ? kr : (N - t.hi.q) / t.lo.q;
                i128 k = denom_free ? kr : std::min(kr, kn);
                if (k <= 0) break;
                t.hi = {t.hi.p + (std::int64_t)k * t.lo.p, t.hi.q + (std::int64_t)k * t.lo.q};
                if (!denom_free && k < kr) break;
            }
        }

        // 残った両境界のうち分母 <= N のものから、target に近い方 (同距離なら小さい方) を選ぶ。
        auto abs_diff = [&](fraction f) {
            i128 v = diff(f.p, f.q);
            return v < 0 ? -v : v;
        };
        fraction best{0, 0};
        bool has = false;
        auto consider = [&](fraction f) {
            if (f.q == 0 || f.q > N) return;
            if (!has) {
                best = f, has = true;
                return;
            }
            // |target - f| vs |target - best| : abs_diff(f)/f.q vs abs_diff(best)/best.q
            i128 l = abs_diff(f) * best.q, r = abs_diff(best) * f.q;
            if (l < r || (l == r && f < best)) best = f;
        };
        consider(t.lo);
        consider(t.hi);
        return best;
    }

    // 単調述語 pred に対する Stern-Brocot 二分探索。
    // pred(p, q) は分数 p/q が小さいほど真になる単調述語 (pred(0/1) は真を仮定)。
    // 「pred が真である最大の分数」のうち分母が max_denominator 以下のものを返す。
    // 各方向の連続ステップ数を二分探索で一括処理するため、述語呼び出しは
    // O(log^2 max_denominator) 回。pred の符号を反転すれば「偽になる最小の分数」も探せる。
    template <class F>
    static fraction search(F pred, std::int64_t max_denominator) {
        const std::int64_t N = max_denominator;
        fraction lo{0, 1}, hi{1, 0};  // pred(lo) は真。lo を最大化していく。
        while (true) {
            fraction m{lo.p + hi.p, lo.q + hi.q};  // mediant
            if (m.q > N) break;                    // 分母上限を超える -> これ以上分割不可
            if (pred(m.p, m.q)) {
                // mediant が真 -> 答えは m 以上。右へ lo += k*hi を進める。
                // lo + k*hi が真を保ち、かつ分母 lo.q + k*hi.q <= N となる最大 k (>=1)。
                // hi.q==0 (hi=+∞) のときは分母が変わらないので分母制約なし -> 述語のみで止める。
                std::int64_t hk = (hi.q == 0) ? step_cap(lo, hi) : (N - lo.q) / hi.q;
                std::int64_t k = max_step(hk, [&](std::int64_t j) { return pred(lo.p + j * hi.p, lo.q + j * hi.q); });
                lo = {lo.p + k * hi.p, lo.q + k * hi.q};
                if (hi.q != 0 && k == hk) break;  // 分母上限に達した -> 確定
            } else {
                // mediant が偽 -> 答えは m 未満。左へ hi += k*lo を進める。
                std::int64_t hk = (lo.q == 0) ? step_cap(hi, lo) : (N - hi.q) / lo.q;
                std::int64_t k = max_step(hk, [&](std::int64_t j) { return !pred(hi.p + j * lo.p, hi.q + j * lo.q); });
                hi = {hi.p + k * lo.p, hi.q + k * lo.q};
                if (lo.q != 0 && k == hk) break;
            }
        }
        return lo;
    }

  private:
    fraction lo, hi;  // 子孫区間の左端・右端

    // base + k*step の分子・分母が int64 を溢れさせない最大 k。
    // step.q==0 (step=+∞) のときの右進み量の上限に使う。
    static std::int64_t step_cap(fraction base, fraction step) {
        constexpr std::int64_t LIM = (std::int64_t)4e18;
        std::int64_t k = LIM;
        if (step.p > 0) k = std::min(k, (LIM - base.p) / step.p);
        if (step.q > 0) k = std::min(k, (LIM - base.q) / step.q);
        return k;
    }

    // ok(j) が j について単調 (真->偽) なとき、ok(j) が真を保つ最大の j を
    // [0, hk] の範囲で返す。ok(0) は真を仮定。倍々+二分で O(log hk) 回呼ぶ。
    template <class G>
    static std::int64_t max_step(std::int64_t hk, G ok) {
        if (hk <= 0) return 0;
        if (ok(hk)) return hk;         // 範囲端まで真
        std::int64_t lo = 0, hi = hk;  // ok(lo)=true, ok(hi)=false
        while (hi - lo > 1) {
            std::int64_t mid = lo + (hi - lo) / 2;
            (ok(mid) ? lo : hi) = mid;
        }
        return lo;
    }

    // 子へ k 回降りる。'L' なら右端を左端側へ、'R' なら左端を右端側へ k 回寄せる。
    constexpr void descend(char c, std::int64_t k) {
        if (c == 'L') hi = {hi.p + lo.p * k, hi.q + lo.q * k};
        else lo = {lo.p + hi.p * k, lo.q + hi.q * k};
    }
};
