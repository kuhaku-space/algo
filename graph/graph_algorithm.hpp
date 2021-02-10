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
    bitset<1 << 20> negative_cycle;

    Graph(int64_t v) : V(v) {
        edges = vector<vector<edge>>(V);
        dist = vector<T>(V);
    }

    const T &operator[](int64_t i) const { return dist[i]; }
    T &operator[](int64_t i) { return dist[i]; }

    void add_edge(int64_t a, int64_t b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
    }
    void add_edges(int64_t a, int64_t b, T d = T(1)) {
        edges[a].push_back(edge{a, b, d});
        edges[b].push_back(edge{b, a, d});
    }

    void dijkstra(int64_t s, T inf = numeric_limits<T>::max()) {
        dist.assign(V, inf);
        priority_queue<edge, vector<edge>, greater<edge>> p_que;
        p_que.push(edge{s, s, T()});
        while (!p_que.empty()) {
            edge e = p_que.top();
            p_que.pop();
            if (e.dist >= dist[e.to]) continue;
            dist[e.to] = e.dist;
            for (auto i : edges[e.to]) p_que.push(e + i);
        }
    }

    void bellman_ford(int64_t s, T inf = numeric_limits<T>::max()) {
        dist.assign(V, inf);
        dist[s] = T();
        negative_cycle = bitset<1 << 20>();

        bool flg = true;
        int64_t cnt = 0;
        while (flg && cnt <= V * 2) {
            flg = false;
            for (int64_t i = 0; i < V; ++i) {
                if (dist[i] == inf) continue;
                for (auto j : edges[i]) {
                    if (chmin(dist[j.to], dist[i] + j.dist)) {
                        flg = true;
                        if (cnt >= V) negative_cycle.set(j.to);
                    }
                }
            }
            ++cnt;
        }
    }

    bool is_visit(int64_t a) const {
        return dist[a] != numeric_limits<T>::max();
    }

    bool is_negative_cycle(int64_t a) const { return negative_cycle[a]; }

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
