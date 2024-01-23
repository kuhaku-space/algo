#include <utility>
#include <vector>
#include "graph/graph.hpp"

/**
 * @brief オイラーツアー
 * @details [参考](https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp)
 *
 * @tparam T 辺の重みの型
 */
template <class T>
struct eular_tour {
    eular_tour(const Graph<T> &_g, int r = 0) : g(_g), ls(_g.size()), rs(_g.size()), pos() {
        this->build(r);
    }

    std::pair<int, int> operator[](int i) const { return {this->ls[i], this->rs[i]}; }

    int size() const { return this->pos; }

    int get_l(int i) const { return this->ls[i]; }
    int get_r(int i) const { return this->rs[i]; }

    template <class F>
    void query(int v, const F &f) const {
        f(this->ls[v], this->rs[v]);
    }

  private:
    const Graph<T> &g;
    std::vector<int> ls, rs;
    int pos;

    void build(int r = 0) {
        this->pos = 0;
        this->dfs(r, -1);
    }

    void dfs(int v, int p) {
        this->ls[v] = this->pos++;
        for (auto &e : this->g[v]) {
            if (e.to() != p) this->dfs(e.to(), v);
        }
        this->rs[v] = this->pos;
    }
};
