#include <algorithm>
#include <iterator>
#include <vector>

/**
 * @brief Mex
 *
 */
struct minimum_excluded {
    minimum_excluded() : n(), _size(), exists(64), v() {}

    constexpr int operator()() const noexcept { return n; }
    constexpr int get() const noexcept { return n; }

    void add(int x) {
        if (x < 0) return;
        ++_size;
        if (_size == (int)std::size(exists)) {
            exists.resize(_size << 1);
            int cnt = 0;
            for (int i = 0; i < (int)std::size(v); ++i) {
                if (v[i] < (int)std::size(exists)) {
                    if (exists[v[i]]) --_size;
                    else exists[v[i]] = true;
                } else {
                    v[cnt++] = v[i];
                }
            }
            v.erase(std::begin(v) + cnt, std::end(v));
        }
        if (x < (int)std::size(exists)) {
            if (exists[x]) --_size;
            else exists[x] = true;
        } else {
            v.emplace_back(x);
        }
        while (exists[n]) ++n;
    }

  private:
    int n, _size;
    std::vector<bool> exists;
    std::vector<int> v;
};
