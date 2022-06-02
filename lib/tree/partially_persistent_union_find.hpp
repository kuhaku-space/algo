#include "template/template.hpp"

/**
 * @brief 部分永続Union-Find
 *
 */
struct partially_persistent_union_find {
    partially_persistent_union_find(int _n)
        : _now(0), _data(_n, std::vector<std::pair<int, int>>(1, {0, -1})) {}

    int root(int x, int t) const {
        auto p = this->_data[x].back();
        if (p.first > t || p.second < 0) return x;
        return this->root(p.second, t);
    }
    int get_root(int x, int t) const { return this->root(x, t); }

    bool is_root(int x, int t) const {
        return this->_data[x].back().first > t || this->_data[x].back().second < 0;
    }

    bool same(int x, int y, int t) const { return this->root(x, t) == this->root(y, t); }
    bool is_same(int x, int y, int t) const { return this->same(x, y, t); }

    int size(int x, int t) const {
        x = this->root(x, t);
        return -std::prev(std::upper_bound(this->_data[x].begin(), this->_data[x].end(),
                                           std::pair<int, int>{t, this->_data.size()}))
                    ->second;
    }
    int get_size(int x, int t) const { return this->size(x, t); }

    int unite(int x, int y) {
        ++_now;
        x = this->root(x, _now), y = this->root(y, _now);
        if (x == y) return _now;
        auto p = this->_data[x].back(), q = this->_data[y].back();
        if (p.second > q.second) swap(x, y), swap(p, q);
        this->_data[x].emplace_back(_now, p.second + q.second);
        this->_data[y].emplace_back(_now, x);
        return _now;
    }

  private:
    int _now;
    std::vector<std::vector<std::pair<int, int>>> _data;
};
