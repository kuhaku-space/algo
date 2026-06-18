#pragma once
#include <functional>
#include <utility>
#include <vector>

/// @brief D 分ヒープ
/// @details `Key`・`Value` を保持し、`Comp` で `Value` を比較する。
///          `Comp = std::greater<>` で `Value` 最小をルートにする最小ヒープになる
///          （`binary_heap` / `fibonacci_heap` と同じ規約）。
///          連続領域（`std::vector`）に `pair<Value, Key>` を並べる flat 実装。
///          decrease-key は持たない。
/// @tparam D 分岐数（既定 4）。二分ヒープより木が浅く（log_D N）、`pop` の
///           sift-down で子をまとめて見るため比較回数が増えるトレードオフがある。
/// @note 当環境のベンチでは Dijkstra 用途で `std::priority_queue` と概ね互角だった
///       （明確な速度優位は確認できなかった）。`binary_heap` と並ぶ汎用ヒープとして提供する。
template <class Key, class Value, class Comp = std::less<>, int D = 4>
struct dary_heap {
    static_assert(D >= 2, "D must be >= 2");

    dary_heap() : data(), comp() {}

    constexpr bool empty() const { return data.empty(); }
    constexpr int size() const { return (int)data.size(); }
    std::pair<Key, Value> top() const { return {data[0].second, data[0].first}; }

    void push(Key key, Value value) {
        data.emplace_back(value, key);
        int index = (int)data.size() - 1;
        // sift-up: 親より「上に来るべき」なら入れ替える。
        while (index > 0) {
            int parent = (index - 1) / D;
            if (!comp(data[parent].first, data[index].first)) break;
            std::swap(data[parent], data[index]);
            index = parent;
        }
    }
    void emplace(Key key, Value value) { push(key, value); }

    void pop() {
        data[0] = data.back();
        data.pop_back();
        int index = 0, n = (int)data.size();
        // sift-down: 子のうち「最も上に来るべき」ものと入れ替える。
        while (true) {
            int first = D * index + 1;
            if (first >= n) break;
            int best = first;
            for (int k = first + 1; k < first + D && k < n; ++k) {
                if (comp(data[best].first, data[k].first)) best = k;
            }
            if (!comp(data[index].first, data[best].first)) break;
            std::swap(data[index], data[best]);
            index = best;
        }
    }

  private:
    // (Value, Key) を並べる。Value 優先で比較するため Value を first に置く。
    std::vector<std::pair<Value, Key>> data;
    Comp comp;
};

/// @brief 4 分ヒープ（`dary_heap` の D=4 固定エイリアス）
/// @details `template <class...> class` 形式（型パラメータのみ）にすることで、
///          `shortest_path<quaternary_heap>` のように template-template 引数として渡せる。
template <class Key, class Value, class Comp = std::less<>>
using quaternary_heap = dary_heap<Key, Value, Comp, 4>;
