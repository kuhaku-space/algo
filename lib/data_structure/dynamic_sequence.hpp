#pragma once
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>
#include "random/xoroshiro128.hpp"

/// @brief 動的配列
template <class M, class UniformRandomBitGenerator = xoroshiro128>
struct dynamic_sequence {
  private:
    using T = typename M::value_type;
    using priority_type = typename UniformRandomBitGenerator::result_type;

    struct node_t {
        using pointer = node_t *;

        static int count(pointer t) { return !t ? 0 : t->cnt; }
        static T composition(pointer t) { return !t ? M::id() : t->acc; }

        node_t(const T &v, priority_type p) : val(v), acc(v), ch{nullptr, nullptr}, priority(p), cnt(1), rev() {}
        node_t(T &&v, priority_type p) : val(v), acc(v), ch{nullptr, nullptr}, priority(p), cnt(1), rev() {}

        T val, acc;
        pointer ch[2];
        priority_type priority;
        int cnt;
        bool rev;
    };

    using node_ptr = typename node_t::pointer;

  public:
    dynamic_sequence() : root(nullptr) {}
    dynamic_sequence(node_ptr p) : root(p) {}

    int size() const { return node_t::count(root); }

    T get(int k) {
        assert(k < node_t::count(root));
        node_ptr node = root;
        while (true) {
            push(node);
            int c = node_t::count(node->ch[0]);
            if (c == k) break;
            if (k < c) node = node->ch[0];
            else node = node->ch[1], k -= c + 1;
        }
        return node->val;
    }

    void set(int k, T val) {
        assert(k < node_t::count(root));
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        while (true) {
            push(node);
            nodes.emplace_back(node);
            int c = node_t::count(node->ch[0]);
            if (c == k) break;
            if (k < c) node = node->ch[0];
            else node = node->ch[1], k -= c + 1;
        }
        node->val = val;
        std::reverse(nodes.begin(), nodes.end());
        for (auto t : nodes) update(t);
    }

    void insert(int k, T val) { root = insert(root, k, val); }
    void push_front(const T &val) {
        node_ptr node = new node_t(val, gen());
        root = merge(node, root);
    }
    void push_front(T &&val) {
        node_ptr node = new node_t(std::move(val), gen());
        root = merge(node, root);
    }
    void push_back(const T &val) {
        node_ptr node = new node_t(val, gen());
        root = merge(root, node);
    }
    void push_back(T &&val) {
        node_ptr node = new node_t(std::move(val), gen());
        root = merge(root, node);
    }

    void erase(int k) { root = erase(root, k); }
    void pop_front() { root = erase(root, 0); }
    void pop_back() { root = erase(root, node_t::count(root) - 1); }

    T prod(int r) const { return prod(root, r); }
    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= node_t::count(root));
        std::pair<node_ptr, node_ptr> p = split(root, l);
        T res = prod(p.second, r - l);
        root = merge(p.first, p.second);
        return res;
    }

    void reverse(int l, int r) {
        std::pair<node_ptr, node_ptr> sr = split(root, r);
        std::pair<node_ptr, node_ptr> sl = split(sr.first, l);
        if (sl.second) sl.second->rev ^= true;
        root = merge(sl.first, sl.second);
        root = merge(root, sr.second);
    }

    int lower_bound(T key) {
        node_ptr node = root;
        int res = 0;
        while (node) {
            int c = node_t::count(node->ch[0]);
            if (node->acc < key) node = node->ch[1], res += c + 1;
            else node = node->ch[0];
        }
        return res;
    }

    std::pair<dynamic_sequence, dynamic_sequence> split(int k) {
        auto [pl, pr] = split(root, k);
        return std::make_pair(dynamic_sequence(pl), dynamic_sequence(pr));
    }
    std::tuple<dynamic_sequence, dynamic_sequence, dynamic_sequence> split(int l, int r) {
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        return std::make_tuple(dynamic_sequence(ql), dynamic_sequence(qr), dynamic_sequence(pr));
    }

    void merge_left(dynamic_sequence lhs) { root = merge(lhs.root, root); }
    void merge_right(dynamic_sequence rhs) { root = merge(root, rhs.root); }

  private:
    static inline UniformRandomBitGenerator gen = UniformRandomBitGenerator();
    node_ptr root;

    void push(node_ptr t) {
        if (t && t->rev) {
            std::swap(t->ch[0], t->ch[1]);
            if (t->ch[0]) t->ch[0]->rev ^= true;
            if (t->ch[1]) t->ch[1]->rev ^= true;
            t->rev = false;
        }
    }

    node_ptr update(node_ptr t) {
        push(t);
        t->cnt = node_t::count(t->ch[0]) + node_t::count(t->ch[1]) + 1;
        t->acc = M::op(M::op(node_t::composition(t->ch[0]), t->val), node_t::composition(t->ch[1]));
        return t;
    }

    node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        push(l);
        push(r);
        if (l->priority > r->priority) {
            l->ch[1] = merge(l->ch[1], r);
            return update(l);
        } else {
            r->ch[0] = merge(l, r->ch[0]);
            return update(r);
        }
    }

    std::pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        if (!t) return std::make_pair<node_ptr, node_ptr>(nullptr, nullptr);
        push(t);
        if (k <= node_t::count(t->ch[0])) {
            auto s = split(t->ch[0], k);
            t->ch[0] = s.second;
            return std::make_pair(s.first, update(t));
        } else {
            auto s = split(t->ch[1], k - node_t::count(t->ch[0]) - 1);
            t->ch[1] = s.first;
            return std::make_pair(update(t), s.second);
        }
    }

    node_ptr insert(node_ptr t, int k, T v) {
        std::pair<node_ptr, node_ptr> s = split(t, k);
        node_ptr res = new node_t(v, gen());
        res = merge(s.first, res);
        res = merge(res, s.second);
        return res;
    }

    node_ptr erase(node_ptr t, int k) {
        push(t);
        int c = node_t::count(t->ch[0]);
        if (k == c) return merge(t->ch[0], t->ch[1]);
        if (k < c) {
            t->ch[0] = erase(t->ch[0], k);
            return update(t);
        } else {
            t->ch[1] = erase(t->ch[1], k - c - 1);
            return update(t);
        }
    }

    T prod(node_ptr t, int r) const {
        assert(0 <= r && r <= node_t::count(t));
        T res = M::id();
        while (r) {
            if (r == node_t::count(t)) {
                res = M::op(res, node_t::composition(t));
                break;
            }
            int c = node_t::count(t->ch[0]);
            if (r < c) {
                t = t->ch[0];
                continue;
            }
            res = M::op(res, node_t::composition(t->ch[0]));
            r -= c;
            if (r) res = M::op(res, t->val), --r;

            t = t->ch[1];
        }
        return res;
    }
};
