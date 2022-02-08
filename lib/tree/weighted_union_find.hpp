#include "template/template.hpp"

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
        if (this->_data[k] < 0) return k;
        auto par = this->find(this->_data[k]);
        this->_weights[k] += this->_weights[this->_data[k]];
        return this->_data[k] = par;
    }

    T get_weight(int t) {
        this->find(t);
        return this->_weights[t];
    }

    bool unite(int x, int y, T w) {
        w += this->get_weight(x) - this->get_weight(y);
        x = find(x), y = find(y);
        if (x == y) return false;
        if (this->_data[x] > this->_data[y]) {
            swap(x, y);
            w *= -1;
        }
        this->_data[x] += this->_data[y];
        this->_data[y] = x;
        this->_weights[y] = w;
        return true;
    }

    T diff(int x, int y) { return this->get_weight(y) - this->get_weight(x); }

  private:
    std::vector<int> _data;
    std::vector<T> _weights;
};
