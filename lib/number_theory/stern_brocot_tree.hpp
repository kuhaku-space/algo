#pragma once
#include <algorithm>
#include <cstdint>
#include <utility>
#include <vector>

/// @brief 既約分数 (Stern-Brocot 木のノード)
///
/// 正の有理数を p/q で表す。0 は 0/1、+∞ は 1/0 として扱える。
/// 比較は __int128 でクロス積を取りオーバーフローを避ける。
/// @complexity すべての操作が $O(1)$
struct sbt_fraction {
    /// @brief 分子pと分母q
    /// @complexity $O(1)$
    std::int64_t p, q;

    /// @brief 0/1を構築する
    /// @complexity $O(1)$
    constexpr sbt_fraction() : p(0), q(1) {}

    /// @brief 分子p、分母qの分数を構築する
    /// @complexity $O(1)$
    constexpr sbt_fraction(std::int64_t p, std::int64_t q) : p(p), q(q) {}

    /// @brief 分子と分母が等しいか返す
    /// @complexity $O(1)$
    friend constexpr bool operator==(const sbt_fraction &a, const sbt_fraction &b) { return a.p == b.p && a.q == b.q; }

    /// @brief クロス積で大小を比較する
    /// @complexity $O(1)$
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
/// @complexity 単純な親子操作は $O(1)$、分数とパスの変換はEuclid法の反復回数に比例
struct stern_brocot_tree {
    /// @brief ノードを表す分数型
    /// @complexity 型エイリアスで実行時計算量はない
    using fraction = sbt_fraction;

    /// @brief 根からの連長圧縮パス型
    /// @complexity 型エイリアスで実行時計算量はない
    using path = std::vector<std::pair<char, std::int64_t>>;

    /// @brief 根1/1を構築する
    /// @complexity $O(1)$
    constexpr stern_brocot_tree() : lo(0, 1), hi(1, 0) {}

    /// @brief 子孫区間(lo, hi)からノードを構築する
    /// @complexity $O(1)$
    constexpr stern_brocot_tree(fraction lo, fraction hi) : lo(lo), hi(hi) {}

    /// @brief 分数fが表すノードを構築する
    /// @details パスの往復を避け、降下を直接lo/hiへ反映する。
    /// @complexity $O(\log\max(p,q))$ 回のEuclid反復
    static stern_brocot_tree from_fraction(fraction f) {
        stern_brocot_tree t;
        walk(f, [&](char c, std::int64_t k) { t.descend(c, k); });
        return t;
    }

    /// @brief 連長圧縮パスを根から辿ったノードを構築する
    /// @complexity パスの要素数を $L$ として $O(L)$
    static stern_brocot_tree from_path(const path &pth) {
        stern_brocot_tree t;
        for (auto [c, k] : pth) t.descend(c, k);
        return t;
    }

    /// @brief このノードが表す既約分数を返す
    /// @complexity $O(1)$
    constexpr fraction value() const { return {lo.p + hi.p, lo.q + hi.q}; }

    /// @brief 子孫が成す開区間の左右端を返す
    /// @complexity $O(1)$
    constexpr std::pair<fraction, fraction> range() const { return {lo, hi}; }

    /// @brief 根1/1か返す
    /// @complexity $O(1)$
    constexpr bool is_root() const { return lo.p == 0 && lo.q == 1 && hi.p == 1 && hi.q == 0; }

    /// @brief 左の子へk回降りた子孫を返す
    /// @complexity $O(1)$
    constexpr stern_brocot_tree left(std::int64_t k = 1) const {
        stern_brocot_tree t = *this;
        t.descend('L', k);
        return t;
    }

    /// @brief 右の子へk回降りた子孫を返す
    /// @complexity $O(1)$
    constexpr stern_brocot_tree right(std::int64_t k = 1) const {
        stern_brocot_tree t = *this;
        t.descend('R', k);
        return t;
    }

    /// @brief 根からの深さを返す
    /// @details パスを構築せず連長を直接足し上げる。根は0。
    /// @complexity $O(\log\max(p,q))$ 回のEuclid反復
    std::int64_t depth() const {
        std::int64_t res = 0;
        walk(value(), [&](char, std::int64_t k) { res += k; });
        return res;
    }

    /// @brief 根からこのノードまでの連長圧縮パスを返す
    /// @complexity $O(\log\max(p,q))$ 回のEuclid反復
    path path_from_root() const { return encode(value()); }

    // --- 静的ユーティリティ (有理数を直接操作) ---

    /// @brief 1/1からfまでの連長圧縮パスを返す
    /// @complexity $O(\log\max(p,q))$ 回のEuclid反復
    static path encode(fraction f) {
        path res;
        walk(f, [&](char c, std::int64_t k) { res.emplace_back(c, k); });
        return res;
    }

    /// @brief パスが指す既約分数を返す
    /// @complexity パスの要素数を $L$ として $O(L)$
    static fraction decode(const path &pth) { return from_path(pth).value(); }

    /// @brief 2分数の最近共通祖先を返す
    /// @complexity 2分数の連長圧縮パス長を $L_1,L_2$ として $O(L_1+L_2)$
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

    /// @brief fの祖先のうち深さkのものを返す
    /// @return 存在しなければ無効値{0, 0}
    /// @complexity fの連長圧縮パス長を $L$ として $O(L)$
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

    /// @brief targetに最も近い、分母がmax_denominator以下の既約分数を返す
    /// @details 距離が等しいときは小さい方を返す。target=1/0は非対応。
    /// @complexity $O(\log\max(p,q,max\_denominator))$
    static fraction nearest(fraction target, std::int64_t max_denominator) {
        using i128 = __int128;
        const i128 R = target.p, D = target.q, N = max_denominator;
        // target との符号付きクロス差 p*D - R*q (0 で一致) と、その絶対値。
        auto diff = [&](i128 p, i128 q) { return p * D - R * q; };
        auto adiff = [&](const fraction &f) {
            i128 v = diff(f.p, f.q);
            return v < 0 ? -v : v;
        };

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
            // dm<0 なら右へ (near=lo, far=hi, descend 'R')、dm>0 なら左へ (near=hi, far=lo, 'L')。
            // どちら向きでも near += k*far で target に寄せる。
            char dir = dm < 0 ? 'R' : 'L';
            fraction near = dm < 0 ? t.lo : t.hi;
            fraction far = dm < 0 ? t.hi : t.lo;
            // near は target と同じ側、far は反対側。k <= |diff(near)| / |diff(far)| で越えない。
            // far がちょうど target (adiff(far)==0) ならこれ以上寄れない。target=1/0 (+∞) で
            // far=hi が初期から +∞ のときもここに入り、0 除算を避ける。
            i128 df = adiff(far);
            if (df == 0) break;
            i128 kr = adiff(near) / df;
            // far.q == 0 (+∞) のときは分母制約がかからない。
            i128 cap = far.q == 0 ? kr : std::min(kr, (i128)(N - near.q) / far.q);
            if (cap <= 0) break;
            t.descend(dir, (std::int64_t)cap);
            if (far.q != 0 && cap < kr) break;  // 分母制約で目標まで進めず終了
        }

        // 残った両境界のうち分母 <= N のものから、target に近い方 (同距離なら小さい方) を選ぶ。
        fraction best{0, 0};
        bool has = false;
        auto consider = [&](fraction f) {
            if (f.q == 0 || f.q > N) return;
            if (!has) {
                best = f, has = true;
                return;
            }
            // |target - f| vs |target - best| : adiff(f)/f.q vs adiff(best)/best.q
            i128 l = adiff(f) * best.q, r = adiff(best) * f.q;
            if (l < r || (l == r && f < best)) best = f;
        };
        consider(t.lo);
        consider(t.hi);
        return best;
    }

    /// @brief 単調述語predが真となる最大の分数を分母上限内で返す
    /// @details pred(p,q)は分数が小さいほど真で、pred(0,1)は真とする。
    /// @complexity 述語呼出し $O(\log^2 max\_denominator)$ 回
    template <class F>
    static fraction search(F pred, std::int64_t max_denominator) {
        const std::int64_t N = max_denominator;
        stern_brocot_tree t;  // pred(lo) は真。lo を最大化していく。
        while (true) {
            fraction m = t.value();
            if (m.q > N) break;  // 分母上限を超える -> これ以上分割不可
            // mediant が真なら答えは m 以上 -> 右へ lo += k*hi。偽なら m 未満 -> 左へ hi += k*lo。
            // どちら向きでも、進める境界 from に対し to += k*from を「規準が真の間」進める。
            bool go_right = pred(m.p, m.q);
            char dir = go_right ? 'R' : 'L';
            const fraction &to = go_right ? t.lo : t.hi;    // 動かす境界
            const fraction &from = go_right ? t.hi : t.lo;  // 加える境界
            // to + k*from が規準を保ち、かつ分母 to.q + k*from.q <= N となる最大 k (>=1)。
            // from.q==0 (+∞) のときは分母が変わらないので分母制約なし -> 規準のみで止める。
            std::int64_t hk = (from.q == 0) ? step_cap(to, from) : (N - to.q) / from.q;
            std::int64_t k = max_step(hk, [&](std::int64_t j) {
                bool ok = pred(to.p + j * from.p, to.q + j * from.q);
                return go_right ? ok : !ok;
            });
            t.descend(dir, k);
            if (from.q != 0 && k == hk) break;  // 分母上限に達した -> 確定
        }
        return t.lo;
    }

  private:
    fraction lo, hi;  // 子孫区間の左端・右端

    // 1/1 から f までの降下を連長圧縮で辿り、各ステップ (移動文字, 連続回数) を
    // visit(c, k) に渡す。encode/from_fraction/depth が共有する。1/1 のとき何もしない。
    template <class V>
    static void walk(fraction f, V visit) {
        std::int64_t a = f.p, b = f.q;
        while (a != 1 || b != 1) {
            if (a > b) {
                std::int64_t k = (a - 1) / b;
                visit('R', k);
                a -= k * b;
            } else {
                std::int64_t k = (b - 1) / a;
                visit('L', k);
                b -= k * a;
            }
        }
    }

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
