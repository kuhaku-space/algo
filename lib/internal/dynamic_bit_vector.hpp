#pragma once
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <random>
#include <vector>

namespace internal {

/// @brief 動的完備辞書
struct dynamic_bit_vector {
  private:
    using priority_type = std::mt19937::result_type;

    struct node_t {
        using pointer = node_t *;

        static unsigned int count(pointer t) { return !t ? 0 : t->cnt; }
        static unsigned int composition(pointer t) { return !t ? 0 : t->sum; }

        node_t(bool v, priority_type p)
            : val(v), sum(v), ch{nullptr, nullptr}, priority(p), cnt(1), len(1) {}

        std::uint64_t val;
        unsigned int sum;
        pointer ch[2];
        priority_type priority;
        unsigned int cnt, len;
    };

    using node_ptr = typename node_t::pointer;

  public:
    dynamic_bit_vector() : root(nullptr), gen() {}

    bool operator[](unsigned int k) const { return get(k); }
    bool get(unsigned int k) const {
        node_ptr t = root;
        while (true) {
            unsigned int c = node_t::count(t->ch[0]);
            if (k < c) {
                t = t->ch[0];
                continue;
            }
            k -= c;
            if (k < t->len) break;
            k -= t->len;
            t = t->ch[1];
        }
        return t->val >> k & 1;
    }

    unsigned int rank(unsigned int k) const { return prod(root, k); }
    unsigned int rank(bool val, unsigned int k) const { return val ? rank(k) : k - rank(k); }

    void insert(unsigned int k, bool f) {
        assert(k <= node_t::count(root));
        if (!root) {
            root = new node_t(f, gen());
            return;
        }
        auto [sl, sr] = split(root, k);
        k -= node_t::count(sl);
        node_ptr t = sl, tmp = nullptr;
        std::vector<node_ptr> nodes;
        while (t->ch[1]) {
            nodes.emplace_back(t);
            t = t->ch[1];
        }
        k += t->len;
        if (t->len < 64) {
            t->val = insert_bit(t->val, k, f);
            t->sum += f;
            ++t->cnt;
            ++t->len;
        } else {
            std::uint64_t ml = (1ul << 32) - 1;
            tmp = new node_t(0, gen());
            tmp->val = (t->val >> 32) & ml;
            tmp->sum = __builtin_popcountl(tmp->val);
            tmp->cnt = 32;
            tmp->len = 32;
            t->val &= ml;
            t->cnt = 32;
            t->len = 32;
            if (k < 32) {
                t->val = insert_bit(t->val, k, f);
                ++t->cnt;
                ++t->len;
            } else {
                tmp->val = insert_bit(tmp->val, k - 32, f);
                tmp->sum += f;
                ++tmp->cnt;
                ++tmp->len;
            }
            nodes.emplace_back(t);
        }
        std::reverse(nodes.begin(), nodes.end());
        for (node_ptr node : nodes) update(node);
        if (tmp) sl = merge(sl, tmp);
        root = merge(sl, sr);
    }

    void erase(unsigned int k) { root = erase(root, k); }

    node_ptr get_root() const { return root; }

  private:
    node_ptr root;
    std::mt19937 gen;

    std::uint64_t insert_bit(std::uint64_t val, unsigned int k, bool f) const {
        std::uint64_t ml = (1ul << k) - 1, mr = ~ml;
        std::uint64_t res = std::uint64_t(f) << k;
        res |= val & ml;
        res |= (val & mr) << 1;
        return res;
    }

    std::uint64_t erase_bit(std::uint64_t val, unsigned int k) const {
        std::uint64_t ml = (1ul << k) - 1, mr = ~ml << 1;
        std::uint64_t res = val & ml;
        res |= (val & mr) >> 1;
        return res;
    }

    node_ptr update(node_ptr t) {
        if (!t) return t;
        t->cnt = node_t::count(t->ch[0]) + node_t::count(t->ch[1]) + t->len;
        t->sum = node_t::composition(t->ch[0]) + __builtin_popcountl(t->val) +
                 node_t::composition(t->ch[1]);
        return t;
    }

    node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        if (l->priority > r->priority) {
            l->ch[1] = merge(l->ch[1], r);
            return update(l);
        } else {
            r->ch[0] = merge(l, r->ch[0]);
            return update(r);
        }
    }

    std::pair<node_ptr, node_ptr> split(node_ptr t, unsigned int k) {
        if (!t) return std::make_pair<node_ptr, node_ptr>(nullptr, nullptr);
        unsigned int c = node_t::count(t->ch[0]);
        if (c <= k && k <= c + t->len) {
            node_ptr l = t, r = t->ch[1];
            t->ch[1] = nullptr;
            return std::make_pair(update(l), r);
        }
        if (k < c) {
            auto s = split(t->ch[0], k);
            t->ch[0] = s.second;
            return std::make_pair(s.first, update(t));
        } else {
            auto s = split(t->ch[1], k - c - t->len);
            t->ch[1] = s.first;
            return std::make_pair(update(t), s.second);
        }
    }

    node_ptr erase(node_ptr t, unsigned int k) {
        assert(k < node_t::count(t));
        unsigned int c = node_t::count(t->ch[0]);
        if (k < c) {
            t->ch[0] = erase(t->ch[0], k);
            return update(t);
        }
        k -= c;
        if (k < t->len) {
            if (t->len == 1) {
                return merge(t->ch[0], t->ch[1]);
            } else {
                t->val = erase_bit(t->val, k);
                --t->len;
                return update(t);
            }
        }
        t->ch[1] = erase(t->ch[1], k - t->len);
        return update(t);
    }

    unsigned int prod(node_ptr t, unsigned int r) const {
        assert(r <= node_t::count(t));
        unsigned int res = 0;
        while (r) {
            if (r == node_t::count(t)) {
                res += node_t::composition(t);
                break;
            }
            unsigned int c = node_t::count(t->ch[0]);
            if (r < c) {
                t = t->ch[0];
                continue;
            }
            res += node_t::composition(t->ch[0]);
            r -= c;
            unsigned int m = std::min(r, t->len);
            if (m) {
                res += __builtin_popcountl((t->val) & ((1ul << m) - 1));
                r -= m;
            }
            t = t->ch[1];
        }
        return res;
    }
};

}  // namespace internal
