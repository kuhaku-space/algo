#include <graph/graph.hpp>
#include <template/template.hpp>

template <class T>
struct heap {
    heap(int n) : _size(), v(1), u(n) {}

    auto top() const { return this->v[1]; }
    int size() const { return this->_size; }
    bool empty() const { return this->_size == 0; }

    void push(int a, T b) {
        if (this->u[a]) {
            this->update(a, b);
            return;
        }
        this->u[a] = ++(this->_size);
        this->v.emplace_back(a, b);

        int idx = this->_size;
        while (idx > 1 && this->v[idx].second < this->v[idx >> 1].second) {
            swap(this->u[a], this->u[this->v[idx >> 1].first]);
            swap(this->v[idx], this->v[idx >> 1]);
            idx >>= 1;
        }
    }
    void emplace(int a, T b) { this->push(a, b); }

    void pop() {
        this->u[this->v[this->_size].first] = 1;
        this->v[1] = this->v[(this->_size)--];
        this->v.pop_back();

        int idx = 1 << 1;
        while (idx <= this->_size) {
            if (idx < this->_size && this->v[idx + 1].second < this->v[idx].second) ++idx;
            if (this->v[idx >> 1].second < this->v[idx].second) break;
            swap(this->u[this->v[idx >> 1].first], this->u[this->v[idx].first]);
            swap(this->v[idx >> 1], this->v[idx]);
            idx <<= 1;
        }
    }

    void update(int a, T b) {
        if (b < this->v[this->u[a]].second) {
            this->v[this->u[a]].second = b;
            int idx = this->u[a];
            while (idx > 1 && this->v[idx].second < this->v[idx >> 1].second) {
                swap(this->u[a], this->u[this->v[idx >> 1].first]);
                swap(this->v[idx], this->v[idx >> 1]);
                idx >>= 1;
            }
        }
    }

  private:
    int _size;
    std::vector<pair<int, T>> v;
    std::vector<int> u;
};

template <class T>
std::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {
    struct _edge {
        int to;
        T dist;
        constexpr _edge() : to(), dist() {}
        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist) {}
        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist; }
        bool operator>(const _edge &rhs) const { return rhs < *this; }
    };
    std::vector<T> dists(g.size(), inf);
    heap<T> p_que(g.size());
    dists[s] = T();
    p_que.emplace(s, T());
    while (!p_que.empty()) {
        auto [to, dist] = p_que.top();
        p_que.pop();
        if (dists[to] < dist) continue;
        for (auto &i : g[to]) {
            if (chmin(dists[i.to], dist + i.dist)) p_que.emplace(i.to, dist + i.dist);
        }
    }
    return dists;
}
