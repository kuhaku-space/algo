#include "_base.hpp"

// https://github.com/beet-aizu/library/blob/master/tree/eulertourforvertex.cpp

struct eular_tour {
    vector<vector<int64_t>> data;
    vector<int64_t> ls, rs;
    int64_t pos;

    eular_tour(int64_t n) : data(n), ls(n), rs(n) {}

    const int64_t &operator[](int64_t i) const { return ls[i]; }

    void add_edge(int64_t a, int64_t b) {
        data[a].emplace_back(b);
        data[b].emplace_back(a);
    }

    void dfs(int64_t v, int64_t p) {
        ls[v] = pos++;
        for (int64_t u : data[v]) {
            if (u != p) dfs(u, v);
            rs[v] = pos;
        }
    }

    void build(int64_t r = 0) {
        pos = 0;
        dfs(r, -1);
    }

    const int64_t &get_l(int64_t i) const { return ls[i]; }
    const int64_t &get_r(int64_t i) const { return rs[i]; }

    template <class F>
    void query(int64_t v, F f) {
        f(ls[v], rs[v]);
    }
};
