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

    friend constexpr bool operator==(const sbt_fraction &a, const sbt_fraction &b) {
        return a.p == b.p && a.q == b.q;
    }
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

  private:
    fraction lo, hi;  // 子孫区間の左端・右端

    // 子へ k 回降りる。'L' なら右端を左端側へ、'R' なら左端を右端側へ k 回寄せる。
    constexpr void descend(char c, std::int64_t k) {
        if (c == 'L') hi = {hi.p + lo.p * k, hi.q + lo.q * k};
        else lo = {lo.p + hi.p * k, lo.q + hi.q * k};
    }
};
