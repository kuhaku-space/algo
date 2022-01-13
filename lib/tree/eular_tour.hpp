#include "template/template.hpp"

/**
 * @brief オイラーツアー
 * @details [参考](https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp)
 *
 */
struct eular_tour {
    eular_tour(int n) : G(n), ls(n), rs(n), pos() {}

    pair<int, int> operator[](int i) const { return make_pair(this->ls[i], this->rs[i]); }

    int size() const { return this->pos; }

    void add_edge(int a, int b) {
        this->G[a].emplace_back(b);
        this->G[b].emplace_back(a);
    }
    void add_edges(int a, int b) { this->add_edge(a, b); }

    void dfs(int v, int p) {
        this->ls[v] = this->pos++;
        for (auto &u : this->G[v]) {
            if (u != p) this->dfs(u, v);
            this->rs[v] = this->pos;
        }
    }

    void build(int r = 0) {
        this->pos = 0;
        this->dfs(r, -1);
    }

    int get_l(int i) const { return this->ls[i]; }
    int get_r(int i) const { return this->rs[i]; }

    template <class F>
    void query(int v, const F &f) const {
        f(this->ls[v], this->rs[v]);
    }

  private:
    vector<vector<int>> G;
    vector<int> ls, rs;
    int pos;
};
