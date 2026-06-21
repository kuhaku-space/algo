#pragma once
#include <functional>
#include <utility>
#include <vector>

/// @brief 二分ヒープ（decrease-key 対応）
/// @details `Key`・`Value` を保持し、`Comp` で `Value` を比較する。
///          `Comp = std::greater<>` で `Value` 最小をルートにする最小ヒープになる
///          （`dary_heap` / `fibonacci_heap` と同じ規約）。
///          連続領域（`std::vector`）に要素を並べる flat 実装で、`new`/`delete` を
///          一切行わない。`push` は安定なハンドルを返し、`pop`/`push`/`update` を
///          挟んでもそのハンドルで同じ要素を指し続けられる（要素はノード ID で
///          管理し、ヒープ配列の再配置から切り離す）。
/// @tparam Comp `Value` の比較子。`comp(a, b) == true` のとき a が b より下位
///              （ルートから遠い側）になる。
template <class Key, class Value, class Comp = std::less<>>
struct binary_heap {
  private:
    static constexpr int nil = -1;

    struct _node {
        Key key;
        Value value;
    };

  public:
    /// @brief `push` が返す安定ハンドル。`update` に渡してその要素を decrease-key する。
    /// @details 既定構築（`handle{}`）は無効値で、`bool` 文脈で `false`。
    ///          要素を `pop` してもハンドルは無効化しない（呼び出し側で寿命を管理する）。
    struct handle {
        constexpr handle() : idx(nil) {}
        constexpr explicit operator bool() const { return idx >= 0; }
        constexpr bool operator==(const handle &) const = default;

      private:
        friend struct binary_heap;
        constexpr explicit handle(int i) : idx(i) {}
        int idx;
    };

    binary_heap() : nodes(), heap(), pos(), comp() {}

    constexpr bool empty() const { return heap.empty(); }
    constexpr int size() const { return (int)heap.size(); }
    std::pair<Key, Value> top() const {
        const _node &n = nodes[heap[0]];
        return {n.key, n.value};
    }

    handle push(Key key, Value value) {
        int id = (int)nodes.size();
        nodes.push_back({std::move(key), std::move(value)});
        pos.push_back((int)heap.size());
        heap.push_back(id);
        sift_up((int)heap.size() - 1);
        return handle(id);
    }
    handle emplace(Key key, Value value) { return push(std::move(key), std::move(value)); }

    void pop() {
        int last = (int)heap.size() - 1;
        swap_heap(0, last);
        heap.pop_back();
        if (!heap.empty()) sift_down(0);
    }

    /// @brief ハンドルの要素を `value` に更新する（ルート側へ近づく更新のみ反映）。
    /// @details `comp(現在値, value) == true`（= 現在値が下位）のときだけ値を上書きし
    ///          sift-up する。最小ヒープ（`greater<>`）では「より小さい値」への
    ///          更新、つまり decrease-key に対応する。逆向きの更新は無視する。
    void update(handle h, Value value) {
        _node &n = nodes[h.idx];
        if (!comp(n.value, value)) return;
        n.value = std::move(value);
        sift_up(pos[h.idx]);
    }

  private:
    // ヒープ配列の i, j を入れ替え、スロット → 位置の対応も同期する。
    void swap_heap(int i, int j) {
        std::swap(heap[i], heap[j]);
        pos[heap[i]] = i;
        pos[heap[j]] = j;
    }

    // i の要素を親より下位な間だけ上へ運ぶ。
    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) >> 1;
            if (!comp(nodes[heap[parent]].value, nodes[heap[i]].value)) break;
            swap_heap(i, parent);
            i = parent;
        }
    }

    // i の要素を子のうち最上位なものより下位な間だけ下へ運ぶ。
    void sift_down(int i) {
        int n = (int)heap.size();
        while (true) {
            int left = 2 * i + 1;
            if (left >= n) break;
            int best = left;
            int right = left + 1;
            if (right < n && comp(nodes[heap[best]].value, nodes[heap[right]].value)) best = right;
            if (!comp(nodes[heap[i]].value, nodes[heap[best]].value)) break;
            swap_heap(i, best);
            i = best;
        }
    }

    std::vector<_node> nodes;  // ノード ID → 要素（ID は安定、解放しない）
    std::vector<int> heap;     // ヒープ位置 → ノード ID
    std::vector<int> pos;      // ノード ID → ヒープ位置
    Comp comp;
};
