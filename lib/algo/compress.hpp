#include "_base.hpp"

struct Compress {
    vector<int64_t> data;
    Compress() {}
    Compress(vector<int64_t> _data) : data(_data) { build(); }

    const int64_t& operator[](int64_t i) const { return data[i]; }
    int64_t& operator[](int64_t i) { return data[i]; }

    void add(int64_t x) { data.emplace_back(x); }

    void build() {
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }
    void build(vector<int64_t> _data) {
        data = _data;
        sort(data.begin(), data.end());
        data.erase(unique(data.begin(), data.end()), data.end());
    }
    int64_t get(int64_t x) {
        return lower_bound(data.begin(), data.end(), data) - data.begin();
    }

    size_t size() { return data.size(); }
};
