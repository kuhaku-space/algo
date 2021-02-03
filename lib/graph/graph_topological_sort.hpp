#include "_base.hpp"

template <class T>
struct Graph {
    struct edge {
        int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const { return dist < rhs.dist; }

        bool operator>(const edge &rhs) const { return dist > rhs.dist; }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) { return edge(*this) += rhs; }
    };

    int64_t V;
    vector<T> dist;
    vector<vector<edge>> edges;

    Graph(int64_t v) : V(v) {
        edges = vector<vector<edge>>(V);
        dist = vector<T>(V, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = 1, bool is_dual = false) {
        edges[a].push_back(edge{a, b, d});
        if (is_dual) edges[b].push_back(edge{b, a, d});
    }

    vector<int64_t> topological_sort() {
        vector<int64_t> res;
        bitset<1 << 20> is_seen;
        for (int64_t i = 0; i < V; ++i) {
            if (is_seen[i]) continue;
            stack<int64_t> st;
            st.push(~i);
            st.push(i);
            while (!st.empty()) {
                auto v = st.top();
                st.pop();
                if (v < 0) {
                    if (!is_seen[~v]) res.push_back(~v);
                    is_seen.set(~v);
                    continue;
                }
                for (auto e : edges[v]) {
                    if (is_seen[e.to]) continue;
                    st.push(~e.to);
                    st.push(e.to);
                }
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
