#pragma once
#include <cassert>
#include <functional>
#include <type_traits>
#include <utility>
#include <vector>

/// @brief Convex Hull Trick (monotone)
///
/// 直線 $ax+b$ を傾き単調順に add し、任意の $x$ における最小値（または最大値）を
/// 二分探索で求める。最小値は `Comp = std::less<>`（既定）で傾きを単調減少順、
/// 最大値は `Comp = std::greater<>` で傾きを単調増加順に add すること。
/// クエリ `get(x)` の $x$ は任意の順で与えてよい。
template <class T, class Comp = std::less<T>>
struct cht {
    /// @brief 直線 $ax+b$ を追加する（傾きは単調順）
    void add(T a, T b) {
        line_t line{a, b};
        if (!lines.empty() && lines.back().a == a) {
            // 同じ傾きはより良い切片だけ残す
            if (!comp(b, lines.back().b)) return;
            lines.pop_back();
        }
        while (lines.size() >= 2 && bad(lines[lines.size() - 2], lines.back(), line)) lines.pop_back();
        lines.push_back(line);
    }

    /// @brief $x$ における最小値（または最大値）
    T get(T x) const {
        assert(!lines.empty());
        int low = 0, high = static_cast<int>(lines.size()) - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (comp(f(lines[mid + 1], x), f(lines[mid], x))) low = mid + 1;
            else high = mid;
        }
        return f(lines[low], x);
    }

    bool empty() const { return lines.empty(); }

  private:
    struct line_t {
        T a, b;
    };

    std::vector<line_t> lines;
    Comp comp;

    static T f(const line_t &line, T x) { return line.a * x + line.b; }

    // 中央の直線 l2 が l1, l3 に隠れて不要かどうかを判定する。
    // 直線 (l1,l2) と (l2,l3) の交点 x 座標が逆順なら l2 は包絡線に現れない。
    // 交点比較を割り算なしの掛け算で行う（整数型では __int128 で桁あふれを防ぐ）。
    // min（傾き単調減少）・max（傾き単調増加）のどちらの追加順でも同じ式で判定できる。
    static bool bad(const line_t &l1, const line_t &l2, const line_t &l3) {
        if constexpr (std::is_integral_v<T>) {
            return static_cast<__int128>(l2.b - l1.b) * (l2.a - l3.a) >=
                   static_cast<__int128>(l3.b - l2.b) * (l1.a - l2.a);
        } else {
            return (l2.b - l1.b) * (l2.a - l3.a) >= (l3.b - l2.b) * (l1.a - l2.a);
        }
    }
};
