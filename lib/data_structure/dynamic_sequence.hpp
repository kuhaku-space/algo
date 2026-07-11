#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 動的配列（AVL 木）
/// @details split/merge は join-based framework（split_last + join）で構成し、AVL の高さ制約により
///          各操作 O(log n) worst-case を保証する。
template <monoid M>
struct DynamicSequence {
  private:
    using T = typename M::value_type;

    struct Node {
        using pointer = Node *;

        static int get_count(pointer t) { return !t ? 0 : t->cnt; }
        static int get_height(pointer t) { return !t ? 0 : t->ht; }
        static T get_composition(pointer t) { return !t ? M::id() : t->acc; }

        Node(const T &v) : val(v), acc(v), ch{nullptr, nullptr}, cnt(1), ht(1), rev() {}
        Node(T &&v) : val(std::move(v)), acc(val), ch{nullptr, nullptr}, cnt(1), ht(1), rev() {}

        T val, acc;
        pointer ch[2];
        int cnt, ht;
        bool rev;

        // erase したノードは再利用しないため、確保のみ行うバンプアロケータで malloc 呼び出し回数を減らす
        static constexpr std::size_t chunk_size = 1 << 16;
        static inline std::vector<Node *> chunks;
        static inline std::size_t chunk_pos = 0;

        static void *operator new(std::size_t) {
            if (chunks.empty() || chunk_pos == chunk_size) {
                chunks.push_back(static_cast<Node *>(::operator new(chunk_size * sizeof(Node))));
                chunk_pos = 0;
            }
            return chunks.back() + (chunk_pos++);
        }
        static void operator delete(void *) noexcept {}
    };

    using node_ptr = typename Node::pointer;

  public:
    DynamicSequence() : root(nullptr) {}
    DynamicSequence(node_ptr p) : root(p) {}

    int size() const { return Node::get_count(root); }

    T get(int k) {
        assert(k < Node::get_count(root));
        node_ptr node = root;
        while (true) {
            push(node);
            int c = Node::get_count(node->ch[0]);
            if (c == k) break;
            if (k < c) node = node->ch[0];
            else node = node->ch[1], k -= c + 1;
        }
        return node->val;
    }

    void set(int k, T val) {
        assert(k < Node::get_count(root));
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        while (true) {
            push(node);
            nodes.emplace_back(node);
            int c = Node::get_count(node->ch[0]);
            if (c == k) break;
            if (k < c) node = node->ch[0];
            else node = node->ch[1], k -= c + 1;
        }
        node->val = val;
        std::reverse(nodes.begin(), nodes.end());
        for (auto t : nodes) update(t);
    }

    void insert(int k, T val) { root = insert(root, k, val); }
    void push_front(const T &val) { root = merge(new Node(val), root); }
    void push_front(T &&val) { root = merge(new Node(std::move(val)), root); }
    void push_back(const T &val) { root = merge(root, new Node(val)); }
    void push_back(T &&val) { root = merge(root, new Node(std::move(val))); }

    void erase(int k) { root = erase(root, k); }
    void pop_front() { root = erase(root, 0); }
    void pop_back() { root = erase(root, Node::get_count(root) - 1); }

    T prod(int r) const { return prod(root, r); }
    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= Node::get_count(root));
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
            push(node);
            int c = Node::get_count(node->ch[0]);
            if (node->acc < key) node = node->ch[1], res += c + 1;
            else node = node->ch[0];
        }
        return res;
    }

    template <class G>
    int max_right(G g) {
        return max_right(0, g);
    }
    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= Node::get_count(root));
        assert(g(M::id()));
        auto [pl, pr] = split(root, l);
        T sm = M::id();
        int r = max_right(pr, sm, g);
        root = merge(pl, pr);
        return l + r;
    }

    template <class G>
    int min_left(G g) {
        return min_left(Node::get_count(root), g);
    }
    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= Node::get_count(root));
        assert(g(M::id()));
        auto [pl, pr] = split(root, r);
        T sm = M::id();
        int cnt = min_left(pl, sm, g);
        root = merge(pl, pr);
        return r - cnt;
    }

    std::pair<DynamicSequence, DynamicSequence> split(int k) {
        auto [pl, pr] = split(root, k);
        return std::make_pair(DynamicSequence(pl), DynamicSequence(pr));
    }
    std::tuple<DynamicSequence, DynamicSequence, DynamicSequence> split(int l, int r) {
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        return std::make_tuple(DynamicSequence(ql), DynamicSequence(qr), DynamicSequence(pr));
    }

    void merge_left(DynamicSequence lhs) { root = merge(lhs.root, root); }
    void merge_right(DynamicSequence rhs) { root = merge(root, rhs.root); }

  private:
    node_ptr root;

    static void push(node_ptr t) {
        if (t && t->rev) {
            std::swap(t->ch[0], t->ch[1]);
            if (t->ch[0]) t->ch[0]->rev ^= true;
            if (t->ch[1]) t->ch[1]->rev ^= true;
            t->rev = false;
        }
    }

    static node_ptr update(node_ptr t) {
        push(t);
        t->cnt = Node::get_count(t->ch[0]) + Node::get_count(t->ch[1]) + 1;
        t->ht = std::max(Node::get_height(t->ch[0]), Node::get_height(t->ch[1])) + 1;
        t->acc = M::op(M::op(Node::get_composition(t->ch[0]), t->val), Node::get_composition(t->ch[1]));
        return t;
    }

    static int bf(node_ptr t) {
        push(t);
        return Node::get_height(t->ch[0]) - Node::get_height(t->ch[1]);
    }

    // d = 0: 右回転 (左の子を根に), d = 1: 左回転 (右の子を根に)
    static node_ptr rotate(node_ptr t, int d) {
        push(t);
        node_ptr c = t->ch[d];
        push(c);
        t->ch[d] = c->ch[d ^ 1];
        c->ch[d ^ 1] = t;
        update(t);
        return update(c);
    }

    static node_ptr rebalance(node_ptr t) {
        if (!t) return t;
        int b = bf(t);
        if (b == 2) {
            if (bf(t->ch[0]) < 0) t->ch[0] = rotate(t->ch[0], 1);
            return rotate(t, 0);
        } else if (b == -2) {
            if (bf(t->ch[1]) > 0) t->ch[1] = rotate(t->ch[1], 0);
            return rotate(t, 1);
        }
        return t;
    }

    // mid を根、l と r をその子として結合する (join-based framework)
    static node_ptr join(node_ptr l, node_ptr mid, node_ptr r) {
        if (Node::get_height(l) > Node::get_height(r) + 1) {
            push(l);
            l->ch[1] = join(l->ch[1], mid, r);
            return rebalance(update(l));
        }
        if (Node::get_height(r) > Node::get_height(l) + 1) {
            push(r);
            r->ch[0] = join(l, mid, r->ch[0]);
            return rebalance(update(r));
        }
        mid->ch[0] = l;
        mid->ch[1] = r;
        return update(mid);
    }

    // t の最右ノードを切り離し {残りの木, 切り離したノード} を返す
    static std::pair<node_ptr, node_ptr> split_last(node_ptr t) {
        push(t);
        if (!t->ch[1]) {
            node_ptr l = t->ch[0];
            t->ch[0] = nullptr;
            return {l, update(t)};
        }
        auto [r2, last] = split_last(t->ch[1]);
        t->ch[1] = r2;
        return {rebalance(update(t)), last};
    }

    static node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        auto [l2, mid] = split_last(l);
        return join(l2, mid, r);
    }

    static std::pair<node_ptr, node_ptr> split(node_ptr t, int k) {
        if (!t) return std::make_pair<node_ptr, node_ptr>(nullptr, nullptr);
        push(t);
        int c = Node::get_count(t->ch[0]);
        if (k <= c) {
            node_ptr old_r = t->ch[1];
            auto s = split(t->ch[0], k);
            node_ptr r = join(s.second, t, old_r);
            return std::make_pair(s.first, r);
        } else {
            node_ptr old_l = t->ch[0];
            auto s = split(t->ch[1], k - c - 1);
            node_ptr l = join(old_l, t, s.first);
            return std::make_pair(l, s.second);
        }
    }

    static node_ptr insert(node_ptr t, int k, T v) {
        if (!t) return new Node(v);
        push(t);
        int c = Node::get_count(t->ch[0]);
        if (k <= c) t->ch[0] = insert(t->ch[0], k, v);
        else t->ch[1] = insert(t->ch[1], k - c - 1, v);
        return rebalance(update(t));
    }

    static node_ptr erase(node_ptr t, int k) {
        push(t);
        int c = Node::get_count(t->ch[0]);
        if (k == c) return merge(t->ch[0], t->ch[1]);
        if (k < c) t->ch[0] = erase(t->ch[0], k);
        else t->ch[1] = erase(t->ch[1], k - c - 1);
        return rebalance(update(t));
    }

    template <class G>
    static int max_right(node_ptr t, T &sm, G g) {
        if (!t) return 0;
        push(t);
        T nxt = M::op(sm, Node::get_composition(t));
        if (g(nxt)) {
            sm = nxt;
            return Node::get_count(t);
        }
        int res = max_right(t->ch[0], sm, g);
        if (res != Node::get_count(t->ch[0])) return res;
        T nxt2 = M::op(sm, t->val);
        if (!g(nxt2)) return res;
        sm = nxt2;
        ++res;
        return res + max_right(t->ch[1], sm, g);
    }

    template <class G>
    static int min_left(node_ptr t, T &sm, G g) {
        if (!t) return 0;
        push(t);
        T nxt = M::op(Node::get_composition(t), sm);
        if (g(nxt)) {
            sm = nxt;
            return Node::get_count(t);
        }
        int res = min_left(t->ch[1], sm, g);
        if (res != Node::get_count(t->ch[1])) return res;
        T nxt2 = M::op(t->val, sm);
        if (!g(nxt2)) return res;
        sm = nxt2;
        ++res;
        return res + min_left(t->ch[0], sm, g);
    }

    static T prod(node_ptr t, int r) {
        assert(0 <= r && r <= Node::get_count(t));
        T res = M::id();
        while (r) {
            push(t);
            if (r == Node::get_count(t)) {
                res = M::op(res, Node::get_composition(t));
                break;
            }
            int c = Node::get_count(t->ch[0]);
            if (r < c) {
                t = t->ch[0];
                continue;
            }
            res = M::op(res, Node::get_composition(t->ch[0]));
            r -= c;
            if (r) res = M::op(res, t->val), --r;

            t = t->ch[1];
        }
        return res;
    }
};
