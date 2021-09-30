#include "template/template.hpp"

template <class T>
struct heap {
    vector<T> data;
    int sz;

    heap() : data(1), sz(0) {}

    void push(T x) {
        data.emplace_back(x);
        for (int it = ++sz; it > 1 && data[it] > data[it >> 1]; it >>= 1) {
            swap(data[it], data[it >> 1]);
        }
    }

    auto top() const { return data[1]; }

    void pop() {
        data[1] = data[sz--];
        data.pop_back();
        for (int it = 1; data[it] < min(data[it << 1], data[(it << 1) | 1]);) {
            it <<= 1;
            if (data[it] < data[it | 1]) ++it;
            swap(data[it], data[it >> 1]);
        }
    }

    int size() const { return sz; }
    bool empty() const { return sz == 0; }
};
