#include "template/template.hpp"

/**
 * @brief 座標圧縮
 *
 * @tparam T 要素の型
 */
template <class T>
struct Compress {
    Compress() {}
    Compress(const vector<T>& _data) : data(_data) { this->build(); }

    const T& operator[](int i) const { return this->data[i]; }
    T& operator[](int i) { return this->data[i]; }

    void add(T x) { this->data.emplace_back(x); }

    void build() {
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }
    void build(const vector<T>& _data) {
        this->data = _data;
        std::sort(this->data.begin(), this->data.end());
        this->data.erase(std::unique(this->data.begin(), this->data.end()), this->data.end());
    }

    int get(T x) {
        auto it = std::lower_bound(this->data.begin(), this->data.end(), x);
        assert(*it == x);
        return it - this->data.begin();
    }

    int size() { return this->data.size(); }

  private:
    std::vector<T> data;
};
