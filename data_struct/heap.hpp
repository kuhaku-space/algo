#include "_base.hpp"

template <class T>
struct heap {
    vector<T> data;
    int64_t sz;

    heap() : data(1 << 20, numeric_limit<T>::min()), sz(0) {}

    void push(T x) {
        data[++sz] = x;
        for (int it = sz; it > 1 && data[it] > data[it / 2]; it >>= 1) {
            swap(data[it], data[it / 2]);
        }
    }

    T top() const { return data[1]; }

    void pop() {
        data[1] = data[sz];
        data[sz--] = numeric_limits<T>::min();
        for (int it = 1; data[it] < min(data[it * 2], data[it * 2 + 1]);) {
            it <<= 1;
            if (data[it] < data[it + 1]) ++it;
            swap(data[it], data[it >> 1]);
        }
    }

    int size() const { return sz; }

    bool empty() const { return sz == 0; }
};
