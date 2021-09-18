#include "template/template.hpp"
#include "graph/graph.hpp"
#include "graph/scc.hpp"

// verify : https://atcoder.jp/contests/practice2/tasks/practice2_h

struct two_sat {
    int n;
    Graph<void> G;

    two_sat(int _n) : n(_n), G(_n * 2) {}

    void add(int i, bool f, int j, bool g) {
        i <<= 1, j <<= 1;
        G.add_edge(i + (f ? 0 : 1), j + (g ? 1 : 0));
        G.add_edge(j + (g ? 0 : 1), i + (f ? 1 : 0));
    }

    vector<int> solve() {
        auto res = scc(G);
        return res;
    }

    bool is_satisfy(const vector<int> &v) {
        for (int i = 0; i < n; ++i) {
            if (v[i * 2] == v[i * 2 + 1]) return false;
        }
        return true;
    }

    vector<bool> build(const vector<int> &v) {
        vector<bool> res(n);
        for (int i = 0; i < n; ++i) res[i] = v[i * 2] < v[i * 2 + 1];
        return res;
    }
};
