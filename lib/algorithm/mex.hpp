#include "template/template.hpp"

/**
 * @brief Mex
 *
 */
struct minimum_excluded {
    minimum_excluded() : n(), _size(), is_exist(64), v() {}

    constexpr int operator()() const noexcept { return this->n; }
    constexpr int get() const noexcept { return this->n; }

    void add(int x) {
        if (x < 0) return;
        ++this->_size;
        if (this->_size == (int)this->is_exist.size()) {
            this->is_exist.resize(this->_size << 1);
            int cnt = 0;
            for (int i = 0; i < (int)this->v.size(); ++i) {
                if (this->v[i] < (int)this->is_exist.size()) {
                    if (this->is_exist[this->v[i]]) --this->_size;
                    else this->is_exist[this->v[i]] = true;
                } else {
                    this->v[cnt++] = this->v[i];
                }
            }
            this->v.erase(this->v.begin() + cnt, this->v.end());
        }
        if (x < (int)this->is_exist.size()) {
            if (this->is_exist[x]) --this->_size;
            else this->is_exist[x] = true;
        } else {
            this->v.emplace_back(x);
        }
        while (this->is_exist[this->n]) ++this->n;
    }

  private:
    int n, _size;
    std::vector<bool> is_exist;
    std::vector<int> v;
};
