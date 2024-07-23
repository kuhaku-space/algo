#pragma once
#include <cassert>
#include <random>
#include <utility>

template <class M, class UniformRandomBitGenerator = std::mt19937>
struct dynamic_sequence {
  private:
    using T = typename M::value_type;
    using priority_type = typename UniformRandomBitGenerator::result_type;

    struct node_t {
        using pointer = node_t *;

        static int count(pointer t) { return !t ? 0 : t->cnt; }
        static T composition(pointer t) { return !t ? M::id() : t->acc; }

        node_t(T v, priority_type p)
            : val(v), acc(v), ch{nullptr, nullptr}, priority(p), cnt(1), rev() {}

        T val, acc;
        pointer ch[2];
        priority_type priority;
        int cnt;
        bool rev;
    };

    using node_ptr = typename node_t::pointer;

  public:
    dynamic_sequence() : root(nullptr) {}

    int size() const { return node_t::count(root); }

    T get(int k) const {
        node_ptr node = root;
        while (true) {
            int c = node_t::count(node->ch[0]);
            if (c == k) break;
            if (k < c) node = node->ch[0];
            else node = node->ch[1], k -= c + 1;
        }
        return node->val;
    }

    void insert(int k, T val) { root = insert(root, k, val); }

    void erase(int k) { root = erase(root, k); }

    T prod(int r) const { return prod(root, r); }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r < node_t::count(root));
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

  private:
    UniformRandomBitGenerator gen;
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
        if (!k) return split(t, 1).second;
        std::pair<node_ptr, node_ptr> s1 = split(t, k);
        std::pair<node_ptr, node_ptr> s2 = split(s1.second, 1);
        return merge(s1.first, s2.second);
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
