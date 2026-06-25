#include <cstdint>
#include <unordered_map>
#include <utility>

/**
 * @brief 動的Union-Find
 *
 */
struct dynamic_union_find {
    dynamic_union_find() : data() {}

    std::int64_t root(std::int64_t x) {
        if (!data.count(x)) data[x] = -1;
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    std::int64_t get_root(std::int64_t x) { return root(x); }

    bool is_root(std::int64_t x) { return data.count(x) && data[x] < 0; }

    bool same(std::int64_t x, std::int64_t y) { return root(x) == root(y); }
    bool is_same(std::int64_t x, std::int64_t y) { return same(x, y); }

    int size(std::int64_t x) { return -data[root(x)]; }
    int get_size(std::int64_t x) { return size(x); }

    void clear() { data.clear(); }

    bool unite(std::int64_t x, std::int64_t y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    template <class F>
    bool unite(std::int64_t x, std::int64_t y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    std::unordered_map<std::int64_t, std::int64_t> data;
};
