#pragma once
#include <cassert>
#include <utility>
#include <vector>

/// @brief interval heap
/// @see https://scrapbox.io/data-structures/Interval_Heap
template <class T>
struct interval_heap {
    constexpr interval_heap() : _size(), data(1) {}

    constexpr bool empty() const { return _size == 0; }
    constexpr int size() const { return _size; }

    T get_max() const {
        assert(_size);
        return data[1];
    }
    T get_min() const {
        assert(_size);
        return _size == 1 ? data[1] : data[2];
    }

    void push(const T &x) {
        data.push_back(x);
        apply();
    }
    void push(T &&x) {
        data.push_back(std::move(x));
        apply();
    }
    template <typename... Args>
    void emplace(Args &&...args) {
        data.emplace_back(std::forward<Args>(args)...);
        apply();
    }

    void pop_max() {
        assert(_size);
        --_size;
        if (_size < 2) {
            if (_size == 1) std::swap(data[1], data[2]);
            data.pop_back();
        } else {
            std::swap(data[1], data.back());
            data.pop_back();
            down(1);
        }
    }

    void pop_min() {
        assert(_size);
        --_size;
        if (_size < 2) {
            data.pop_back();
        } else {
            std::swap(data[2], data.back());
            data.pop_back();
            up(2);
        }
    }

  private:
    int _size;
    std::vector<T> data;

    std::pair<int, int> next(int k) {
        assert(k != 2 && _size >= 2);
        if (k & 1) {
            if (k * 2 + 1 <= _size) {
                k = k * 2 + 1;
                return std::make_pair(k, k + 2 <= _size ? k + 2 : k);
            }
            ++k;
            if (k <= _size) return std::make_pair(k, k);
        }
        k = (k / 2) & ~1;
        return std::make_pair(k, k);
    }

    std::pair<int, int> prev(int k) {
        assert(k != 1);
        if (~k & 1) {
            if (k * 2 - 1 <= _size) {
                k *= 2;
                if (k + 2 <= _size) return std::make_pair(k, k + 2);
                if (k <= _size) return std::make_pair(k, k);
            }
            --k;
            return std::make_pair(k, k);
        }
        k = (k / 2 - 1) | 1;
        return std::make_pair(k, k);
    }

    int down(int k) {
        while (k != 2) {
            auto &&[x, y] = next(k);
            if (x != y && data[x] < data[y]) std::swap(x, y);
            if (data[x] < data[k]) break;
            std::swap(data[x], data[k]);
            k = x;
        }
        return k;
    }

    int up(int k) {
        while (k != 1) {
            auto &&[x, y] = prev(k);
            if (x != y && data[y] < data[x]) std::swap(x, y);
            if (data[k] < data[x]) break;
            std::swap(data[k], data[x]);
            k = x;
        }
        return k;
    }

    void apply() {
        ++_size;
        if (_size >= 3) {
            int k = _size;
            k = down(k);
            k = up(k);
        } else if (_size == 2 && data[1] < data[2]) {
            std::swap(data[1], data[2]);
        }
    }
};
