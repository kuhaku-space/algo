#include "template/template.hpp"

/**
 * @brief Undo可能Union-Find
 * @details Implement (union by size)
 *
 * @see https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
 */
struct undo_union_find {
    undo_union_find() : data(), history() {}
    undo_union_find(int _n) : data(_n, -1), history() {}

    int root(int x) { return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]); }
    int get_root(int k) { return this->root(k); }

    bool is_root(int k) const { return this->data[0] < 0; }

    bool same(int x, int y) { return this->root(x) == this->root(y); }
    bool is_same(int x, int y) { return this->same(x, y); }

    int size(int k) { return -this->data[this->root(k)]; }
    int get_size(int k) { return this->size(k); }

    bool unite(int x, int y) {
        x = this->root(x), y = this->root(y);
        this->history.emplace(x, this->data[x]);
        this->history.emplace(y, this->data[y]);
        if (x == y) return false;
        if (this->data[x] > this->data[y]) std::swap(x, y);
        this->data[x] += this->data[y];
        this->data[y] = x;
        return true;
    }

    void undo() {
        this->data[this->history.top().first] = this->history.top().second;
        this->history.pop();
        this->data[this->history.top().first] = this->history.top().second;
        this->history.pop();
    }

    int snapshot() const { return this->history.size(); }

    void rollback(int x = 0) {
        while ((int)(this->history.size()) > x) this->undo();
    }

  private:
    std::vector<int> data;
    std::stack<std::pair<int, int>> history;
};
