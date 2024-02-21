#include <utility>
#include <vector>

/**
 * @brief 重み付き素集合データ構造
 *
 * @tparam T
 */
template <class T>
struct weighted_union_find {
    weighted_union_find() {}
    weighted_union_find(int size) : _data(size, -1), _weights(size) {}

    int find(int k) {
        if (_data[k] < 0) return k;
        int par = find(_data[k]);
        _weights[k] += _weights[_data[k]];
        return _data[k] = par;
    }

    T get_weight(int t) {
        find(t);
        return _weights[t];
    }

    /**
     * @brief v[y] = v[x] + w
     *
     * @param x
     * @param y
     * @param w
     * @return true unite correctly
     * @return false already united
     */
    bool unite(int x, int y, T w) {
        w += get_weight(x) - get_weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (_data[x] > _data[y]) {
            std::swap(x, y);
            w *= -1;
        }
        _data[x] += _data[y];
        _data[y] = x;
        _weights[y] = w;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }
    bool is_same(int x, int y) { return same(x, y); }

    /**
     * @brief get diff between x and y
     *
     * @param x
     * @param y
     * @return T v[y] - v[x]
     */
    T diff(int x, int y) { return get_weight(y) - get_weight(x); }
    T get_diff(int x, int y) { return diff(x, y); }

  private:
    std::vector<int> _data;
    std::vector<T> _weights;
};
