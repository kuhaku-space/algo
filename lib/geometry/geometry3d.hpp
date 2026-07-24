#include "template/template.hpp"

/// @brief 三次元の点・球と最小包含球
/// @details `Pos<T>` と `Circle3<T>`、点集合を覆う球を反復的に求める `min_ball` を提供する。
/// @complexity 基本演算は $O(1)$。`min_ball` は点数を $n$ として
/// $O(n\log(1/\mathrm{EPS}))$
template <class T>
struct Pos {
    /// @brief x・y・z 座標
    /// @complexity $O(1)$ で参照可能
    T x, y, z;
    /// @brief 原点を作る
    /// @complexity $O(1)$
    constexpr Pos() : x(), y(), z() {}
    /// @brief 座標 `(_x, _y, _z)` の点を作る
    /// @complexity $O(1)$
    constexpr Pos(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
};

/// @brief 三次元の球
/// @complexity 構築とフィールド参照は $O(1)$
template <class T>
struct Circle3 {
    /// @brief 球の中心
    /// @complexity $O(1)$ で参照可能
    Pos<T> p;
    /// @brief 球の半径
    /// @complexity $O(1)$ で参照可能
    T r;
    /// @brief 中心 `_p`、半径 `_r` の球を作る
    /// @complexity $O(1)$
    constexpr Circle3(Pos<T> _p, T _r) : p(_p), r(_r) {}
};

/// @brief 点集合 `ps` を覆う球を反復近似で求める
/// @param p 中心の初期値
/// @complexity $O(n\log(1/\mathrm{EPS}))$
template <class T>
Circle3<T> min_ball(std::vector<Pos<T>> &ps, Pos<T> p = {0.0, 0.0, 0.0}) {
    auto dist = [](const Pos<T> &a, const Pos<T> &b) -> T {
        T dx = a.x - b.x;
        T dy = a.y - b.y;
        T dz = a.z - b.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    };

    T r = 0.0, move = 0.5;
    Pos<T> k = {0.0, 0.0, 0.0};
    while (move > EPS * EPS) {
        r = 0.0;
        for (Pos<T> i : ps)
            if (chmax(r, dist(p, i))) k = i;
        p.x += (k.x - p.x) * move;
        p.y += (k.y - p.y) * move;
        p.x += (k.z - p.z) * move;
        move *= 0.999;
    }

    return Circle3<T>(p, r);
}
