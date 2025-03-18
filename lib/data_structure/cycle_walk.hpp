#pragma once
#include <algorithm>
#include <cstdint>

struct cycle_walk {
    cycle_walk(std::int64_t _n) : n(_n) {}

    /// @brief sからgへ負の向きに進むときの距離
    std::int64_t walk_left(std::int64_t s, std::int64_t g) const { return walk_right(g, s); }

    /// @brief sからgへ正の向きに進むときの距離
    std::int64_t walk_right(std::int64_t s, std::int64_t g) const {
        return s <= g ? g - s : n - s + g;
    }

    /// @brief sからgへ向かうときの最小距離
    std::int64_t walk_min(std::int64_t s, std::int64_t g) const {
        return std::min(walk_left(s, g), walk_right(s, g));
    }

    /// @brief sからgへ向かうときの最大距離
    std::int64_t walk_max(std::int64_t s, std::int64_t g) const {
        return std::max(walk_left(s, g), walk_right(s, g));
    }

    /// @brief sからgへ負の向きに進むとき，vを通るか
    bool pass_left(std::int64_t s, std::int64_t g, std::int64_t v) const {
        return pass_right(g, s, v);
    }

    /// @brief sからgへ正の向きに進むとき，vを通るか
    bool pass_right(std::int64_t s, std::int64_t g, std::int64_t v) const {
        return (s <= g ? s <= v && v <= g : !(g < v && v < s));
    }

  private:
    std::int64_t n;
};
