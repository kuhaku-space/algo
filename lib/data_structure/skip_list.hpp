#pragma once
#include <algorithm>
#include <array>
#include <bit>
#include <cassert>
#include <optional>
#include "random/xorshift.hpp"

/// @brief スキップリスト
template <class T, int B = 20, class UniformRandomBitGenerator = Xorshift>
struct skip_list {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        std::array<int, B> count;
        std::array<pointer, B> itr;

        constexpr _node() : val(), count(), itr{} {}
        constexpr _node(const T &_val) : val(_val), count{}, itr{} {}
        constexpr _node(T &&_val) : val(std::move(_val)), count{}, itr{} {}
        template <typename... Args>
        constexpr _node(Args &&...args) : val(std::forward<Args>(args)...), count{}, itr{} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    skip_list() : head(new _node()), _size() {}

    constexpr bool empty() const { return _size == 0; }
    constexpr int size() const { return _size; }

    constexpr T get(int k) {
        assert(0 <= k && k < size());
        auto node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->count[i] <= k) k -= node->count[i], node = node->itr[i];
        }
        return node->val;
    }

    template <typename... Args>
    void emplace(Args &&...args) {
        node_ptr new_node = new _node(std::forward<Args>(args)...);
        insert_node(new_node);
    }
    void insert(const T &val) {
        node_ptr new_node = new _node(val);
        insert_node(new_node);
    }
    void insert(T &&val) {
        node_ptr new_node = new _node(val);
        insert_node(new_node);
    }

    void erase(const T &val) {
        node_ptr deleted_node = select_deleted_node(val);
        if (!deleted_node) return;
        --_size;
        node_ptr node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
            if (node->itr[i] == deleted_node)
                node->count[i] += deleted_node->count[i] - 1, node->itr[i] = node->itr[i]->itr[i];
            else --node->count[i];
        }
    }

    bool contains(const T &val) const {
        node_ptr node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
            if (node->itr[i] && node->itr[i]->val == val) return true;
        }
        return false;
    }

    int count(const T &val) const { return upper_bound(val) - lower_bound(val); }

    int lower_bound(const T &val) const {
        int res = 0;
        auto node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) res += node->count[i], node = node->itr[i];
        }
        return res + node->count[0];
    }

    int upper_bound(const T &val) const {
        int res = 0;
        auto node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && !(val < node->itr[i]->val)) res += node->count[i], node = node->itr[i];
        }
        return res + node->count[0];
    }

    std::optional<T> floor(const T &val) const {
        auto node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && !(val < node->itr[i]->val)) node = node->itr[i];
        }
        return node == head ? std::nullopt : std::optional<T>(node->val);
    }

    std::optional<T> ceil(const T &val) const {
        auto node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
        }
        return node->itr[0] == nullptr ? std::nullopt : std::optional<T>(node->itr[0]->val);
    }

  private:
    static inline UniformRandomBitGenerator gen = UniformRandomBitGenerator();
    node_ptr head;
    int _size;

    constexpr int create_height() { return std::min(B - 1, std::countl_zero(gen())); }

    void insert_node(node_ptr new_node) {
        ++_size;
        node_ptr node = head;
        int c = lower_bound(new_node->val);
        int height = create_height();
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < new_node->val) c -= node->count[i], node = node->itr[i];
            if (i <= height) {
                new_node->count[i] = node->count[i] - c + 1, new_node->itr[i] = node->itr[i];
                node->count[i] = c, node->itr[i] = new_node;
            } else {
                ++node->count[i];
            }
        }
    }

    node_ptr select_deleted_node(const T &val) {
        node_ptr node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
        }
        return node->itr[0] && node->itr[0]->val == val ? node->itr[0] : nullptr;
    }
};
