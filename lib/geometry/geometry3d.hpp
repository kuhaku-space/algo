#include "template/template.hpp"

template <class T>
struct Pos {
    T x, y, z;
    constexpr Pos() : x(), y(), z() {}
    constexpr Pos(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
};

template <class T>
struct Circle3 {
    Pos<T> p;
    T r;
    constexpr Circle3(Pos<T> _p, T _r) : p(_p), r(_r) {}
};

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
