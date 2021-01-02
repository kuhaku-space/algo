#include "_base.hpp"

template <class T>
struct heap {
    vector<T> data;
    int64_t sz;

    heap() {
        data.assign(1 << 20, numeric_limits<T>::min());
        sz = 0;
    }

    void push(T x) {
        data[++sz] = x;
        for (int64_t it = sz; it > 1 && data[it] > data[it / 2]; it >>= 1) {
            swap(data[it], data[it / 2]);
        }
    }

    T top() const {
        return data[1];
    }

    void pop() {
        data[1] = data[sz];
        data[sz--] = -LINF;
        for (int64_t it = 1;
             data[it] < data[it * 2] || data[it] < data[it * 2 + 1]; ) {
            it <<= 1;
            if (data[it] < data[it + 1]) ++it;
            swap(data[it], data[it / 2]);
        }
    }

    int64_t size() const {
        return sz;
    }

    int64_t empty() const {
        return sz == 0;
    }
};
