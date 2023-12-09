#include <cassert>
#include <utility>
#include <vector>

struct hopcroft_karp {
    hopcroft_karp(int _n, int _m) : n(_n), m(_m), g(_n), match_left(_n, -1), match_right(_m, -1) {}

    void add_edge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < m);
        g[u].emplace_back(v);
    }

    int matching() {
        int flow = 0;
        std::vector<int> root(n), prev(n), qq(n);
        for (bool updated = true; updated;) {
            updated = false;
            int qi = 0, qj = 0;
            std::fill(root.begin(), root.end(), -1);
            std::fill(prev.begin(), prev.end(), -1);
            for (int i = 0; i < n; i++) {
                if (match_left[i] == -1) qq[qj++] = i, root[i] = i, prev[i] = i;
            }
            while (qi < qj) {
                int u = qq[qi++];
                if (match_left[root[u]] != -1) continue;
                for (int v : g[u]) {
                    if (match_right[v] == -1) {
                        while (v != -1)
                            match_right[v] = u, std::swap(match_left[u], v), u = prev[u];
                        updated = true, flow++;
                        break;
                    }

                    if (prev[match_right[v]] == -1)
                        v = match_right[v], prev[v] = u, root[v] = root[u], qq[qj++] = v;
                }
            }
        }
        return flow;
    }

    std::vector<std::pair<int, int>> get_pairs() const {
        std::vector<std::pair<int, int>> res;
        for (int i = 0; i < n; i++) {
            if (~match_left[i]) res.emplace_back(i, match_left[i]);
        }
        return res;
    }

  private:
    const int n, m;
    std::vector<std::vector<int>> g;
    std::vector<int> match_left, match_right;
};
