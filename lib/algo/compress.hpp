#include "template/template.hpp"

/**
 * @brief 座標圧縮
 *
 * @tparam T
 */
template <class T>
struct Compress {
    vector<T> data;
    Compress() {}
    Compress(const vector<T>& _data) : data(_data) { build(); }

    const T& operator[](int i) const { return data[i]; }
    T& operator[](int i) { return data[i]; }

    void add(T x) { data.emplace_back(x); }

    void build() {
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }
    void build(const vector<T>& _data) {
        data = _data;
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }
    int get(T x) {
        auto it = lower_bound(data.begin(), data.end(), x);
        assert(*it == x);
        return it - data.begin();
    }

    int size() { return data.size(); }
};
