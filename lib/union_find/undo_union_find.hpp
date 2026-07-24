#include <stack>
#include <utility>
#include <vector>

/// @brief Undo可能Union-Find
/// @details 経路圧縮を行わず、union by sizeと変更履歴で状態を巻き戻す。
/// @complexity `root`・`same`・`unite`・`size` は $O(\log n)$、`undo` は
/// $O(1)$、`rollback` は取り消す併合回数に比例
/// @see https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
struct undo_union_find {
    /// @brief 空の Union-Find を作る
    /// @complexity $O(1)$
    undo_union_find() : data(), history() {}
    /// @brief `n` 個の単集合を作る
    /// @complexity $O(n)$
    undo_union_find(int _n) : data(_n, -1), history() {}

    /// @brief `x` の代表を返す
    /// @complexity $O(\log n)$
    int root(int x) const { return data[x] < 0 ? x : root(data[x]); }
    /// @brief `root(k)` の別名
    /// @complexity $O(\log n)$
    int get_root(int k) const { return root(k); }

    /// @brief `k` が集合の代表なら true を返す
    /// @complexity $O(1)$
    bool is_root(int k) const { return data[k] < 0; }

    /// @brief `x`, `y` が同じ集合なら true を返す
    /// @complexity $O(\log n)$
    bool same(int x, int y) const { return root(x) == root(y); }
    /// @brief `same(x, y)` の別名
    /// @complexity $O(\log n)$
    bool is_same(int x, int y) const { return same(x, y); }

    /// @brief `k` が属する集合の要素数を返す
    /// @complexity $O(\log n)$
    int size(int k) const { return -data[root(k)]; }
    /// @brief `size(k)` の別名
    /// @complexity $O(\log n)$
    int get_size(int k) const { return size(k); }

    /// @brief `x`, `y` の集合を併合し、操作履歴を追加する
    /// @return 新たに併合したなら true
    /// @complexity $O(\log n)$
    bool unite(int x, int y) {
        x = root(x), y = root(y);
        history.emplace(x, data[x]);
        history.emplace(y, data[y]);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    /// @brief 最後の `unite` 1 回分を取り消す
    /// @complexity $O(1)$
    void undo() {
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
    }

    /// @brief 現在の状態を表す履歴位置を返す
    /// @complexity $O(1)$
    int snapshot() const { return history.size(); }

    /// @brief 履歴位置 `x` の状態まで併合を取り消す
    /// @complexity 取り消す `unite` の回数に比例
    void rollback(int x = 0) {
        while ((int)(history.size()) > x) undo();
    }

  private:
    std::vector<int> data;
    std::stack<std::pair<int, int>> history;
};
