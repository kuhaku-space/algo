#pragma once
#include <iterator>
#include <utility>
#include <vector>

namespace internal {

/// @brief CSR（Compressed Sparse Row）形式で隣接リストを保持する軽量な内部データ構造
/// @tparam E 各辺に付随するペイロード型（`int` なら単純な隣接先のみ、任意の構造体も可）
///
/// 全辺が確定した状態で一括構築する（ACL 由来）。頂点ごとに動的な `vector` を持たず
/// 1 本の連続領域に詰めるため、重み・辺 ID を保持しない用途（SCC の逆グラフ、
/// HL 分解、2-SAT の含意グラフなど）では `list_graph<T>` / `csr_graph<T>` より軽量。
template <class E>
struct Csr {
    std::vector<int> start;
    std::vector<E> elist;

    Csr() : start(1), elist() {}
    explicit Csr(int n, const std::vector<std::pair<int, E>> &edges) : start(n + 1), elist(edges.size()) {
        for (auto &e : edges) ++start[e.first + 1];
        for (int i = 0; i < n; ++i) start[i + 1] += start[i];
        auto counter = start;
        for (auto &e : edges) elist[counter[e.first]++] = e.second;
    }

    /// @brief 頂点 v の隣接辺を走査する軽量 view（CSR の連続領域を指す）
    struct adjacency {
        using const_iterator = typename std::vector<E>::const_iterator;

        adjacency(const_iterator first, const_iterator last) : _first(first), _last(last) {}

        const_iterator begin() const { return _first; }
        const_iterator end() const { return _last; }

      private:
        const_iterator _first, _last;
    };

    constexpr int size() const { return (int)start.size() - 1; }
    adjacency operator[](int v) const {
        return adjacency(std::next(elist.begin(), start[v]), std::next(elist.begin(), start[v + 1]));
    }
};

}  // namespace internal
