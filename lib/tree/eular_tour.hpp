#include <utility>
#include <vector>
#include "graph/graph.hpp"

/**
 * @brief オイラーツアー
 * @see https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp
 *
 * @tparam T 辺の重みの型
 */
template <class T>
struct eular_tour {
    eular_tour(const Graph<T> &_g, int r = 0) : g(_g), ls(_g.size()), rs(_g.size()), pos() {
        build(r);
    }

    std::pair<int, int> operator[](int i) const { return std::make_pair(ls[i], rs[i]); }

    int size() const { return pos; }

    int get_l(int i) const { return ls[i]; }
    int get_r(int i) const { return rs[i]; }

    template <class F>
    void query(int v, const F &f) const {
        f(ls[v], rs[v]);
    }

  private:
    const Graph<T> &g;
    std::vector<int> ls, rs;
    int pos;

    void build(int r = 0) {
        pos = 0;
        dfs(r, -1);
    }

    void dfs(int v, int p) {
        ls[v] = pos++;
        for (auto &e : g[v]) {
            if (e.to() != p) dfs(e.to(), v);
        }
        rs[v] = pos;
    }
};
