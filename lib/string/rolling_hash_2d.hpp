#pragma once
#include <cassert>
#include <cstdint>
#include <random>
#include <string>
#include <vector>
#include "math/hashint.hpp"

/// @brief 二次元ローリングハッシュ
/// @details 行方向・列方向にそれぞれ別の基数を持つ二次元 Horner 法で構築する。
///          `base_x`/`base_y` はプログラム実行のたびに乱数で決まる（意図的な衝突を避けるため）。
struct RollingHash2D {
    RollingHash2D() : _h(0), _w(0), data(1, std::vector<HashInt>(1)), px(1, HashInt(1)), py(1, HashInt(1)) {}

    template <class T>
    explicit RollingHash2D(const std::vector<std::vector<T>> &grid,
                           HashInt base_x = (std::uint64_t)std::random_device()() + 2,
                           HashInt base_y = (std::uint64_t)std::random_device()() + 2)
        : _h(grid.size()), _w(_h ? grid[0].size() : 0), base_x(base_x), base_y(base_y),
          data(_h + 1, std::vector<HashInt>(_w + 1)), px(_h + 1, HashInt(1)), py(_w + 1, HashInt(1)) {
        for (int i = 1; i <= _h; ++i) px[i] = px[i - 1] * base_x;
        for (int j = 1; j <= _w; ++j) py[j] = py[j - 1] * base_y;
        for (int i = 0; i < _h; ++i) {
            for (int j = 0; j < _w; ++j) {
                data[i + 1][j + 1] = data[i][j + 1] * base_x + data[i + 1][j] * base_y - data[i][j] * base_x * base_y +
                                     HashInt(grid[i][j]);
            }
        }
    }
    explicit RollingHash2D(const std::vector<std::string> &grid,
                           HashInt base_x = (std::uint64_t)std::random_device()() + 2,
                           HashInt base_y = (std::uint64_t)std::random_device()() + 2)
        : RollingHash2D(to_grid(grid), base_x, base_y) {}

    /// 複数の二次元配列を同じ乱数基数でハッシュ化する
    template <class T>
    static std::vector<RollingHash2D> make_many(const std::vector<std::vector<std::vector<T>>> &grids) {
        HashInt base_x = (std::uint64_t)std::random_device()() + 2;
        HashInt base_y = (std::uint64_t)std::random_device()() + 2;
        std::vector<RollingHash2D> res;
        res.reserve(grids.size());
        for (const auto &grid : grids) res.emplace_back(grid, base_x, base_y);
        return res;
    }
    static std::vector<RollingHash2D> make_many(const std::vector<std::vector<std::string>> &grids) {
        HashInt base_x = (std::uint64_t)std::random_device()() + 2;
        HashInt base_y = (std::uint64_t)std::random_device()() + 2;
        std::vector<RollingHash2D> res;
        res.reserve(grids.size());
        for (const auto &grid : grids) res.emplace_back(grid, base_x, base_y);
        return res;
    }

    /// this と同じ乱数基数で別の二次元配列をハッシュ化する
    template <class T>
    RollingHash2D derive(const std::vector<std::vector<T>> &grid) const {
        return RollingHash2D(grid, base_x, base_y);
    }
    RollingHash2D derive(const std::vector<std::string> &grid) const { return RollingHash2D(grid, base_x, base_y); }

    HashInt get_base_x() const { return base_x; }
    HashInt get_base_y() const { return base_y; }

    /// 盤面全体のハッシュ
    HashInt get() const { return get(0, _h, 0, _w); }

    /// grid[x1...x2)[y1...y2) のハッシュ
    HashInt get(int x1, int x2, int y1, int y2) const {
        assert(0 <= x1 && x1 <= x2 && x2 <= _h);
        assert(0 <= y1 && y1 <= y2 && y2 <= _w);
        return data[x2][y2] - data[x1][y2] * px[x2 - x1] - data[x2][y1] * py[y2 - y1] +
               data[x1][y1] * px[x2 - x1] * py[y2 - y1];
    }

  private:
    int _h, _w;
    HashInt base_x, base_y;
    std::vector<std::vector<HashInt>> data;
    std::vector<HashInt> px, py;

    static std::vector<std::vector<char>> to_grid(const std::vector<std::string> &grid) {
        std::vector<std::vector<char>> g(grid.size());
        for (std::size_t i = 0; i < grid.size(); ++i) g[i].assign(grid[i].begin(), grid[i].end());
        return g;
    }
};
