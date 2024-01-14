#include <stack>
#include <utility>
#include <vector>

/**
 * @brief Undo可能Union-Find
 * @details Implement (union by size)
 *
 * @see https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
 */
struct undo_union_find {
    undo_union_find() : data(), history() {}
    undo_union_find(int _n) : data(_n, -1), history() {}

    int root(int x) { return data[x] < 0 ? x : root(data[x]); }
    int get_root(int k) { return root(k); }

    bool is_root(int k) const { return data[k] < 0; }

    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }

    int size(int k) { return -data[root(k)]; }
    int get_size(int k) { return size(k); }

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

    void undo() {
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
    }

    int snapshot() const { return history.size(); }

    void rollback(int x = 0) {
        while ((int)(history.size()) > x) undo();
    }

  private:
    std::vector<int> data;
    std::stack<std::pair<int, int>> history;
};
