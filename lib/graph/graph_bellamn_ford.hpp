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
        dist = vector<T>(V, numeric_limits<T>::max());
    }

    void add_edge(int64_t a, int64_t b, T d = 1, bool is_dual = false) {
        edges[a].push_back(edge{a, b, d});
        if (is_dual) edges[b].push_back(edge{b, a, d});
    }

    void bellman_ford(int64_t s) {
        dist.assign(V, numeric_limits<T>::max());
        dist[s] = T();
        negative_cycle = bitset<1 << 20>();

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

    const T get_dist(int64_t a) const { return dist[a]; }

    bool is_visit(int64_t a) const {
        return dist[a] != numeric_limits<T>::max();
    }

    bool is_negative_cycle(int64_t a) const { return negative_cycle[a]; }
};
