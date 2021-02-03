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
        dist = vector<T>(V);
    }

    const T &operator[](int64_t i) const { return dist[i]; }
    T &operator[](int64_t i) { return dist[i]; }

    void add_edge(int64_t a, int64_t b, T d = T(1), bool is_dual = false) {
        edges[a].push_back(edge{a, b, d});
        if (is_dual) edges[b].push_back(edge{b, a, d});
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
};
