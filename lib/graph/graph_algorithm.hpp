#include "_base.hpp"
#include "graph/union_find.hpp"

template <class T>
struct Graph {
    struct edge {
        int64_t from, to;
        T dist;

        bool operator<(const edge &rhs) const {
            return dist < rhs.dist;
        }
        
        bool operator>(const edge &rhs) const {
            return dist > rhs.dist;
        }

        edge &operator+=(const edge &rhs) {
            to = rhs.to;
            dist += rhs.dist;
            return *this;
        }
        edge operator+(const edge &rhs) {
            return edge(*this) += rhs;
        }
    };

    int64_t V;
    vector<T> dist;
    vector<vector<edge>> edges;
    bitset<1048576> negative_cycle;

    Graph(int64_t v) : V(v) {
        edges.resize(v);
        dist.assign(v, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = 1) {
        edges[a].push_back(edge{a, b, d});
        // edges[b].push_back(edge{b, a, d});
    }

    void dijkstra(int64_t s) {
        dist.assign(V, numeric_limits<T>::max());
        priority_queue<edge, vector<edge>, greater<edge>> p_que;
        p_que.push(edge{s, s, T()});
        while (!p_que.empty()) {
            edge e = p_que.top(); p_que.pop();
            if (e.dist >= dist[e.to]) continue;
            dist[e.to] = e.dist;
            for (auto i : edges[e.to]) p_que.push(e + i);
        }
    }

    void bellman_ford(int64_t s){
        dist.assign(V, numeric_limits<T>::max());
        dist[s] = T();
        negative_cycle = bitset<1048576>();

        bool flg = true;
        int64_t cnt = 0;
        while (flg && cnt <= V * 2) {
            flg = false;
            for (int64_t i = 0; i < V; ++i) {
                if (dist[i] == numeric_limits<T>::max()) continue;
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

    T get_dist(int64_t a) {
        return dist[a];
    }

    bool is_visit(int64_t a) {
        return dist[a] != numeric_limits<T>::max();
    }

    bool is_negative_cycle(int64_t a) {
        return negative_cycle[a];
    }/*

    T kruskal() {
        union_find uf(V);
        T res = T();
        vector<edge> edge_list;
        for (auto v : edges) {
            for (auto e : v) edge_list.push_back(e);
        }
        sort(edge_list.begin(), edge_list.end());
        for (edge e : edge_list) {
            if (!uf.is_same(e.from, e.to)) {
                uf.unite(e.from, e.to);
                res += e.dist;
            }
        }
        return res;
    }*/

    vector<int64_t> topological_sort() {
        vector<int64_t> res;
        bitset<1048576> is_seen;
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
