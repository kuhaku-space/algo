#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 動的配列（スプレー木、反転可能）
/// @details 親ポインタを持つ反復版 splay で根に運んだノードを起点に split/merge を構成する
///          （amortized O(log n)）。全ての操作（読み取り専用のクエリも含む）で対象位置を
///          根まで splay する。AVL 版（join-based framework）と比較し、reverse のような
///          split して戻す操作の再結合コストが軽いためこちらを採用している。
template <monoid M>
struct DynamicSequence {
  private:
    using T = typename M::value_type;

    struct Node {
        using pointer = Node *;

        static int get_size(pointer node) { return !node ? 0 : node->size; }
        static T get_product(pointer node) { return !node ? M::id() : node->product; }

        Node(const T &v) : value(v), product(v), children{nullptr, nullptr}, parent(nullptr), size(1), reversed() {}
        Node(T &&v)
            : value(std::move(v)), product(value), children{nullptr, nullptr}, parent(nullptr), size(1), reversed() {}

        T value, product;
        pointer children[2];
        pointer parent;
        int size;
        bool reversed;

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

    int size() const { return Node::get_size(root); }

    T get(int k) {
        assert(k < Node::get_size(root));
        root = access(root, k);
        return root->value;
    }

    void set(int k, T val) {
        assert(k < Node::get_size(root));
        root = access(root, k);
        root->value = val;
        update(root);
    }

    void insert(int k, const T &val) { root = insert(root, k, new Node(val)); }
    void insert(int k, T &&val) { root = insert(root, k, new Node(std::move(val))); }
    template <class... Args>
    void emplace(int k, Args &&...args) {
        root = insert(root, k, new Node(T(std::forward<Args>(args)...)));
    }
    void push_front(const T &val) { root = merge(new Node(val), root); }
    void push_front(T &&val) { root = merge(new Node(std::move(val)), root); }
    void push_back(const T &val) { root = merge(root, new Node(val)); }
    void push_back(T &&val) { root = merge(root, new Node(std::move(val))); }

    void erase(int k) {
        assert(k < Node::get_size(root));
        auto [erased, rest] = erase(root, k);
        (void)erased;
        root = rest;
    }
    void pop_front() { erase(0); }
    void pop_back() { erase(Node::get_size(root) - 1); }

    T prod(int r) { return prod(0, r); }
    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        if (l == r) return M::id();
        auto [a, b, c] = split3(root, l, r);
        T res = Node::get_product(b);
        root = merge3(a, b, c);
        return res;
    }

    void reverse(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        if (b) b->reversed ^= true;
        root = merge3(a, b, c);
    }

    int lower_bound(T key) {
        node_ptr node = root;
        int res = 0;
        while (node) {
            push(node);
            int left_size = Node::get_size(node->children[0]);
            if (node->product < key) node = node->children[1], res += left_size + 1;
            else node = node->children[0];
        }
        return res;
    }

    template <class G>
    int max_right(G g) {
        return max_right(0, g);
    }
    template <class G>
    int max_right(int l, G g) {
        assert(0 <= l && l <= Node::get_size(root));
        assert(g(M::id()));
        auto [pl, pr] = split(root, l);
        T sm = M::id();
        int r = max_right(pr, sm, g);
        root = merge(pl, pr);
        return l + r;
    }

    template <class G>
    int min_left(G g) {
        return min_left(Node::get_size(root), g);
    }
    template <class G>
    int min_left(int r, G g) {
        assert(0 <= r && r <= Node::get_size(root));
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
        auto [a, b, c] = split3(root, l, r);
        return std::make_tuple(DynamicSequence(a), DynamicSequence(b), DynamicSequence(c));
    }

    void merge_left(DynamicSequence lhs) { root = merge(lhs.root, root); }
    void merge_right(DynamicSequence rhs) { root = merge(root, rhs.root); }

  private:
    node_ptr root;

    static void push(node_ptr node) {
        if (!node) return;
        if (node->reversed) {
            std::swap(node->children[0], node->children[1]);
            if (node->children[0]) node->children[0]->reversed ^= true;
            if (node->children[1]) node->children[1]->reversed ^= true;
            node->reversed = false;
        }
    }

    static node_ptr update(node_ptr node) {
        node->size = Node::get_size(node->children[0]) + Node::get_size(node->children[1]) + 1;
        node->product =
            M::op(M::op(Node::get_product(node->children[0]), node->value), Node::get_product(node->children[1]));
        return node;
    }

    static void set_child(node_ptr p, node_ptr c, int dir) {
        push(p);
        p->children[dir] = c;
        if (c) c->parent = p;
        update(p);
    }
    static void cut_child(node_ptr p, int dir) {
        push(p);
        if (p->children[dir]) {
            p->children[dir]->parent = nullptr;
            p->children[dir] = nullptr;
            update(p);
        }
    }

    static void zig(node_ptr p, node_ptr v) {
        if ((p->children[0] = v->children[1]) != nullptr) p->children[0]->parent = p;
        update(p);
        v->children[1] = p;
        p->parent = v;
        update(v);
    }
    static void zag(node_ptr p, node_ptr v) {
        if ((p->children[1] = v->children[0]) != nullptr) p->children[1]->parent = p;
        update(p);
        v->children[0] = p;
        p->parent = v;
        update(v);
    }
    static void zig_zig(node_ptr q, node_ptr p, node_ptr v) {
        if ((q->children[0] = p->children[1]) != nullptr) q->children[0]->parent = q;
        update(q);
        p->children[1] = q;
        q->parent = p;
        zig(p, v);
    }
    static void zig_zag(node_ptr q, node_ptr p, node_ptr v) {
        if ((p->children[1] = v->children[0]) != nullptr) p->children[1]->parent = p;
        update(p);
        if ((q->children[0] = v->children[1]) != nullptr) q->children[0]->parent = q;
        update(q);
        v->children[0] = p;
        v->children[1] = q;
        p->parent = q->parent = v;
        update(v);
    }
    static void zag_zag(node_ptr q, node_ptr p, node_ptr v) {
        if ((q->children[1] = p->children[0]) != nullptr) q->children[1]->parent = q;
        update(q);
        p->children[0] = q;
        q->parent = p;
        zag(p, v);
    }
    static void zag_zig(node_ptr q, node_ptr p, node_ptr v) {
        if ((p->children[0] = v->children[1]) != nullptr) p->children[0]->parent = p;
        update(p);
        if ((q->children[1] = v->children[0]) != nullptr) q->children[1]->parent = q;
        update(q);
        v->children[1] = p;
        v->children[0] = q;
        p->parent = q->parent = v;
        update(v);
    }

    static void splay(node_ptr v) {
        for (node_ptr p = v->parent, u = v; p;) {
            if (!p->parent) {
                push(p), push(v);
                if (p->children[0] == u) zig(p, v);
                else zag(p, v);
                break;
            } else {
                node_ptr q = p->parent, r = q->parent;
                push(q), push(p), push(v);
                if (q->children[0] == p) {
                    if (p->children[0] == u) zig_zig(q, p, v);
                    else zig_zag(q, p, v);
                } else {
                    if (p->children[1] == u) zag_zag(q, p, v);
                    else zag_zig(q, p, v);
                }
                p = r, u = q;
            }
        }
        v->parent = nullptr;
    }

    static node_ptr access(node_ptr node, int k) {
        node_ptr v = node;
        while (true) {
            push(v);
            int left_size = Node::get_size(v->children[0]);
            if (k == left_size) break;
            if (k < left_size) v = v->children[0];
            else v = v->children[1], k -= left_size + 1;
        }
        splay(v);
        return v;
    }

    static std::pair<node_ptr, node_ptr> split(node_ptr node, int k) {
        if (!node) return {nullptr, nullptr};
        if (k >= node->size) return {node, nullptr};
        node = access(node, k);
        node_ptr left = node->children[0];
        cut_child(node, 0);
        return {left, node};
    }

    static std::tuple<node_ptr, node_ptr, node_ptr> split3(node_ptr node, int l, int r) {
        auto [ab, c] = split(node, r);
        if (l == 0) return {nullptr, ab, c};
        auto [a, b] = split(ab, l - 1);
        node_ptr rest = b->children[1];
        cut_child(b, 1);
        set_child(b, a, 0);
        return {b, rest, c};
    }

    static node_ptr merge(node_ptr l, node_ptr r) {
        if (!l) return r;
        if (!r) return l;
        node_ptr node = l;
        while (true) {
            push(node);
            if (!node->children[1]) break;
            node = node->children[1];
        }
        splay(node);
        set_child(node, r, 1);
        return node;
    }

    static node_ptr merge3(node_ptr a, node_ptr b, node_ptr c) {
        if (a) set_child(a, b, 1);
        else a = b;
        if (c) set_child(c, a, 0);
        else c = a;
        return c;
    }

    static node_ptr insert(node_ptr node, int k, node_ptr leaf) {
        auto [l, r] = split(node, k);
        set_child(leaf, l, 0);
        return merge(leaf, r);
    }

    static std::pair<node_ptr, node_ptr> erase(node_ptr node, int k) {
        node = access(node, k);
        node_ptr l = node->children[0];
        node_ptr r = node->children[1];
        node->children[0] = node->children[1] = nullptr;
        if (l) l->parent = nullptr;
        if (r) r->parent = nullptr;
        return {node, merge(l, r)};
    }

    template <class G>
    static int max_right(node_ptr node, T &sm, G g) {
        if (!node) return 0;
        push(node);
        T nxt = M::op(sm, Node::get_product(node));
        if (g(nxt)) {
            sm = nxt;
            return Node::get_size(node);
        }
        int res = max_right(node->children[0], sm, g);
        if (res != Node::get_size(node->children[0])) return res;
        T nxt2 = M::op(sm, node->value);
        if (!g(nxt2)) return res;
        sm = nxt2;
        ++res;
        return res + max_right(node->children[1], sm, g);
    }

    template <class G>
    static int min_left(node_ptr node, T &sm, G g) {
        if (!node) return 0;
        push(node);
        T nxt = M::op(Node::get_product(node), sm);
        if (g(nxt)) {
            sm = nxt;
            return Node::get_size(node);
        }
        int res = min_left(node->children[1], sm, g);
        if (res != Node::get_size(node->children[1])) return res;
        T nxt2 = M::op(node->value, sm);
        if (!g(nxt2)) return res;
        sm = nxt2;
        ++res;
        return res + min_left(node->children[0], sm, g);
    }
};
