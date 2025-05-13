#pragma once
#include <cassert>
#include <utility>
#include <vector>

/// @brief Interval Heap
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

    std::pair<int, int> next(int idx) {
        assert(idx != 2 && _size >= 2);
        if (idx & 1) {
            if (idx * 2 + 1 <= _size) {
                idx = idx * 2 + 1;
                return std::make_pair(idx, idx + 2 <= _size ? idx + 2 : idx);
            }
            ++idx;
            if (idx <= _size) return std::make_pair(idx, idx);
        }
        idx = (idx / 2) & ~1;
        return std::make_pair(idx, idx);
    }

    std::pair<int, int> prev(int idx) {
        assert(idx != 1);
        if (~idx & 1) {
            if (idx * 2 - 1 <= _size) {
                idx = idx * 2;
                if (idx + 2 <= _size) return std::make_pair(idx, idx + 2);
                if (idx <= _size) return std::make_pair(idx, idx);
            }
            --idx;
            return std::make_pair(idx, idx);
        }
        idx = (idx / 2 - 1) | 1;
        return std::make_pair(idx, idx);
    }

    int down(int idx) {
        while (idx != 2) {
            auto &&[x, y] = next(idx);
            if (x != y && data[x] < data[y]) std::swap(x, y);
            if (data[x] < data[idx]) break;
            std::swap(data[x], data[idx]);
            idx = x;
        }
        return idx;
    }

    int up(int idx) {
        while (idx != 1) {
            auto &&[x, y] = prev(idx);
            if (x != y && data[y] < data[x]) std::swap(x, y);
            if (data[idx] < data[x]) break;
            std::swap(data[idx], data[x]);
            idx = x;
        }
        return idx;
    }

    void apply() {
        ++_size;
        if (_size >= 3) {
            int idx = _size;
            idx = down(idx);
            idx = up(idx);
        } else if (_size == 2 && data[1] < data[2]) {
            std::swap(data[1], data[2]);
        }
    }
};
