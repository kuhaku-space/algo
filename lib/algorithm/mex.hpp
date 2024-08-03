#pragma once
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
        if (_size == (int)exists.size()) {
            exists.resize(_size << 1);
            v.erase(std::remove_if(v.begin(), v.end(),
                                   [&](int y) {
                                       if (y < (int)exists.size()) {
                                           if (exists[y]) --_size;
                                           else exists[y] = true;
                                           return true;
                                       }
                                       return false;
                                   }),
                    v.end());
        }
        if (x < (int)exists.size()) {
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
