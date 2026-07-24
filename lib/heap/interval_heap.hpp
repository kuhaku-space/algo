#pragma once
#include <cassert>
#include <utility>
#include <vector>

/// @brief interval heap
/// @see https://scrapbox.io/data-structures/Interval_Heap
template <class T>
struct interval_heap {
    /// @brief 空のinterval heapを構築する
    /// @complexity $O(1)$
    constexpr interval_heap() : _size(), data(1) {}

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return _size == 0; }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 最大値を返す
    /// @complexity $O(1)$
    T get_max() const {
        assert(_size);
        return data[1];
    }
    /// @brief 最小値を返す
    /// @complexity $O(1)$
    T get_min() const {
        assert(_size);
        return _size == 1 ? data[1] : data[2];
    }

    /// @brief 値を追加する
    /// @complexity $O(\log n)$
    void push(const T &x) {
        data.push_back(x);
        fix_up();
    }
    /// @brief 値をムーブして追加する
    /// @complexity $O(\log n)$
    void push(T &&x) {
        data.push_back(std::move(x));
        fix_up();
    }
    /// @brief 値を直接構築して追加する
    /// @complexity $O(\log n)$
    template <typename... Args>
    void emplace(Args &&...args) {
        data.emplace_back(std::forward<Args>(args)...);
        fix_up();
    }

    /// @brief 最大値を削除する
    /// @complexity $O(\log n)$
    void pop_max() {
        assert(_size);
        --_size;
        if (_size < 2) {
            if (_size == 1) std::swap(data[1], data[2]);
            data.pop_back();
        } else {
            std::swap(data[1], data.back());
            data.pop_back();
            sift_down(1);
        }
    }

    /// @brief 最小値を削除する
    /// @complexity $O(\log n)$
    void pop_min() {
        assert(_size);
        --_size;
        if (_size < 2) {
            data.pop_back();
        } else {
            std::swap(data[2], data.back());
            data.pop_back();
            sift_up(2);
        }
    }

  private:
    int _size;
    std::vector<T> data;

    // sift_down で下りる先の候補インデックス対を返す。
    std::pair<int, int> down_pair(int k) {
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

    // sift_up で上る先の候補インデックス対を返す。
    std::pair<int, int> up_pair(int k) {
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

    int sift_down(int k) {
        while (k != 2) {
            auto &&[x, y] = down_pair(k);
            if (x != y && data[x] < data[y]) std::swap(x, y);
            if (data[x] < data[k]) break;
            std::swap(data[x], data[k]);
            k = x;
        }
        return k;
    }

    int sift_up(int k) {
        while (k != 1) {
            auto &&[x, y] = up_pair(k);
            if (x != y && data[y] < data[x]) std::swap(x, y);
            if (data[k] < data[x]) break;
            std::swap(data[k], data[x]);
            k = x;
        }
        return k;
    }

    // push 直後の末尾要素をヒープ条件へ整える。
    void fix_up() {
        ++_size;
        if (_size >= 3) {
            int k = _size;
            k = sift_down(k);
            k = sift_up(k);
        } else if (_size == 2 && data[1] < data[2]) {
            std::swap(data[1], data[2]);
        }
    }
};
