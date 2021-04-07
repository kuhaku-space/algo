#include "_base.hpp"

struct radix_heap {
    vector<unsigned int> v[33];
    unsigned int last, sz;
    bool is_top;

    radix_heap() : last(), sz(), is_top() {}

    int bsr(unsigned int x) {
        if (x == 0) return -1;
        return 31-__builtin_clz(x);
    }

    void push(unsigned int x) {
        assert(x >= last);
        ++sz;
        v[bsr(x ^ last) + 1].emplace_back(x);
    }

    unsigned int top() {
        if (is_top) pop();
        is_top = true;
        return last;
    }

    void pop() {
        if (is_top) {
            is_top = false;
            return;
        }
        assert(sz);
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) ++i;
            auto new_last = *min_element(v[i].begin(), v[i].end());
            for (auto x : v[i]) {
                v[bsr(x ^ new_last) + 1].emplace_back(x);
            }
            last = new_last;
            v[i].clear();
        }
        --sz;
        v[0].pop_back();
    }
};

struct radix_heap_64 {
    vector<uint64_t> v[65];
    uint64_t last, sz;
    bool is_top;

    radix_heap_64() : last(), sz(), is_top() {}

    int bsr(uint64_t x) {
        if (x == 0) return -1;
        return 63-__builtin_clz(x);
    }

    void push(uint64_t x) {
        assert(x >= last);
        ++sz;
        v[bsr(x ^ last) + 1].emplace_back(x);
    }

    uint64_t top() {
        if (!is_top) pop();
        is_top = true;
        return last;
    }

    void pop() {
        if (is_top) {
            is_top = false;
            return;
        }
        assert(sz);
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) ++i;
            auto new_last = *min_element(v[i].begin(), v[i].end());
            for (auto x : v[i]) v[bsr(x ^ new_last) + 1].emplace_back(x);
            last = new_last;
            v[i].clear();
        }
        --sz;
        v[0].pop_back();
    }
};

template <class T>
struct radix_heap_dijkstra {
    vector<T> v[33];
    T last;
    unsigned int sz;
    bool is_top;

    radix_heap() : last(), sz(), is_top() {}

    int bsr(unsigned int x) {
        if (x == 0) return -1;
        return 31-__builtin_clz(x);
    }

    bool empty() const {
        return sz == 0;
    }
    auto size() const {
        return sz;
    }

    void push(T x) {
        assert(x.dist >= last.dist);
        ++sz;
        v[bsr(x.dist ^ last.dist) + 1].emplace_back(x);
    }

    auto top() {
        if (!is_top) pop();
        is_top = true;
        return last;
    }

    void pop() {
        if (is_top) {
            is_top = false;
            return;
        }
        assert(sz);
        if (!v[0].size()) {
            int i = 1;
            while (!v[i].size()) ++i;
            auto new_last = *min_element(v[i].begin(), v[i].end());
            for (auto x : v[i]) {
                v[bsr(x.dist ^ new_last.dist) + 1].emplace_back(x);
            }
            v[i].clear();
        }
        --sz;
        last = v[0].back();
        v[0].pop_back();
    }
};
