#include "template/template.hpp"

/**
 * @brief Mex
 *
 */
struct minimum_excluded {
    minimum_excluded() : n(), _size(), exists(64), v() {}

    constexpr int operator()() const noexcept { return this->n; }
    constexpr int get() const noexcept { return this->n; }

    void add(int x) {
        if (x < 0) return;
        ++this->_size;
        if (this->_size == (int)this->exists.size()) {
            this->exists.resize(this->_size << 1);
            int cnt = 0;
            for (int i = 0; i < (int)this->v.size(); ++i) {
                if (this->v[i] < (int)this->exists.size()) {
                    if (this->exists[this->v[i]]) --this->_size;
                    else this->exists[this->v[i]] = true;
                } else {
                    this->v[cnt++] = this->v[i];
                }
            }
            this->v.erase(this->v.begin() + cnt, this->v.end());
        }
        if (x < (int)this->exists.size()) {
            if (this->exists[x]) --this->_size;
            else this->exists[x] = true;
        } else {
            this->v.emplace_back(x);
        }
        while (this->exists[this->n]) ++this->n;
    }

  private:
    int n, _size;
    std::vector<bool> exists;
    std::vector<int> v;
};
