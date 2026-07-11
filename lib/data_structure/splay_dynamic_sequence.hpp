#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 遅延伝播動的配列（スプレー木、反転可能）
/// @details 親ポインタを持つ反復版 splay で根に運んだノードを起点に split/merge を構成する
///          （amortized O(log n)）。全ての操作（読み取り専用のクエリも含む）で対象位置を
///          根まで splay する。
/// @tparam S データのモノイド
/// @tparam F 作用素モノイド（op が作用素の合成、f が値への作用）
template <class S, class F>
requires monoid<S> && monoid<F> && acts_on<F, typename S::value_type>
struct SplayDynamicSequence {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

    struct Node {
        using pointer = Node *;

        static int get_size(pointer node) { return !node ? 0 : node->size; }
        static T get_product(pointer node) { return !node ? S::id() : node->product; }

        Node(const T &v)
            : value(v), product(v), lazy(F::id()), children{nullptr, nullptr}, parent(nullptr), size(1), reversed(),
              has_lazy() {}
        Node(T &&v)
            : value(std::move(v)), product(value), lazy(F::id()), children{nullptr, nullptr}, parent(nullptr), size(1),
              reversed(), has_lazy() {}

        T value, product;
        U lazy;
        pointer children[2];
        pointer parent;
        int size;
        bool reversed;
        bool has_lazy;

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
    SplayDynamicSequence() : root(nullptr) {}
    SplayDynamicSequence(node_ptr p) : root(p) {}

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

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        if (l == r) return S::id();
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

    void apply(int p, U f) { apply(p, p + 1, f); }
    void apply(int l, int r, U f) {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        if (l == r) return;
        auto [a, b, c] = split3(root, l, r);
        all_apply(b, f);
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
        assert(g(S::id()));
        auto [pl, pr] = split(root, l);
        T sm = S::id();
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
        assert(g(S::id()));
        auto [pl, pr] = split(root, r);
        T sm = S::id();
        int cnt = min_left(pl, sm, g);
        root = merge(pl, pr);
        return r - cnt;
    }

    std::pair<SplayDynamicSequence, SplayDynamicSequence> split(int k) {
        auto [pl, pr] = split(root, k);
        return std::make_pair(SplayDynamicSequence(pl), SplayDynamicSequence(pr));
    }
    std::tuple<SplayDynamicSequence, SplayDynamicSequence, SplayDynamicSequence> split(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        return std::make_tuple(SplayDynamicSequence(a), SplayDynamicSequence(b), SplayDynamicSequence(c));
    }

    void merge_left(SplayDynamicSequence lhs) { root = merge(lhs.root, root); }
    void merge_right(SplayDynamicSequence rhs) { root = merge(root, rhs.root); }

  private:
    node_ptr root;

    static void all_apply(node_ptr node, U f) {
        if (!node) return;
        node->value = F::f(f, node->value);
        node->product = F::f(f, node->product);
        node->lazy = node->has_lazy ? F::op(f, node->lazy) : f;
        node->has_lazy = true;
    }

    static void push(node_ptr node) {
        if (!node) return;
        if (node->reversed) {
            std::swap(node->children[0], node->children[1]);
            if (node->children[0]) node->children[0]->reversed ^= true;
            if (node->children[1]) node->children[1]->reversed ^= true;
            node->reversed = false;
        }
        if (node->has_lazy) {
            all_apply(node->children[0], node->lazy);
            all_apply(node->children[1], node->lazy);
            node->has_lazy = false;
        }
    }

    static node_ptr update(node_ptr node) {
        node->size = Node::get_size(node->children[0]) + Node::get_size(node->children[1]) + 1;
        node->product =
            S::op(S::op(Node::get_product(node->children[0]), node->value), Node::get_product(node->children[1]));
        return node;
    }

    // p の dir 側の子を c にする（親ポインタも更新）
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

    // v は p の左の子。v を1段だけ昇格させる（右回転）。
    static void zig(node_ptr p, node_ptr v) {
        if ((p->children[0] = v->children[1]) != nullptr) p->children[0]->parent = p;
        update(p);
        v->children[1] = p;
        p->parent = v;
        update(v);
    }
    // v は p の右の子。v を1段だけ昇格させる（左回転）。
    static void zag(node_ptr p, node_ptr v) {
        if ((p->children[1] = v->children[0]) != nullptr) p->children[1]->parent = p;
        update(p);
        v->children[0] = p;
        p->parent = v;
        update(v);
    }
    // q -> p -> v が左-左（zig-zig）: 同方向に2回回転
    static void zig_zig(node_ptr q, node_ptr p, node_ptr v) {
        if ((q->children[0] = p->children[1]) != nullptr) q->children[0]->parent = q;
        update(q);
        p->children[1] = q;
        q->parent = p;
        zig(p, v);
    }
    // q -> p -> v が左-右（zig-zag）: 逆方向に2回回転
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
    // q -> p -> v が右-右（zag-zag）
    static void zag_zag(node_ptr q, node_ptr p, node_ptr v) {
        if ((q->children[1] = p->children[0]) != nullptr) q->children[1]->parent = q;
        update(q);
        p->children[0] = q;
        q->parent = p;
        zag(p, v);
    }
    // q -> p -> v が右-左（zag-zig）
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

    // v を根まで splay する（zig-zig を省略すると特定の入力列で木が退化し O(n) per query に
    // なる既知の落とし穴があるため、zig-zig と zig-zag を区別して回転する）。
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

    // node を根とする部分木のうち位置 k (0-indexed) にあたるノードを見つけて根まで splay する。
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

    // 位置 k で分割する。位置 k のノードを根まで splay し、その左部分木を切り離すだけで済む。
    // (k == 0 でも実際に位置 0 のノードへ access する。split3 が「戻り値の第2要素は特定の1
    //  ノードであり、その右部分木がそのまま次の境界になる」という前提に依拠しているため。)
    static std::pair<node_ptr, node_ptr> split(node_ptr node, int k) {
        if (!node) return {nullptr, nullptr};
        if (k >= node->size) return {node, nullptr};
        node = access(node, k);
        node_ptr left = node->children[0];
        cut_child(node, 0);
        return {left, node};
    }

    // [0, l) と [l, r) と [r, n) の3分割
    static std::tuple<node_ptr, node_ptr, node_ptr> split3(node_ptr node, int l, int r) {
        auto [ab, c] = split(node, r);
        if (l == 0) return {nullptr, ab, c};
        auto [a, b] = split(ab, l - 1);
        node_ptr rest = b->children[1];
        cut_child(b, 1);
        set_child(b, a, 0);
        return {b, rest, c};
    }

    // l の最右ノードを根まで splay して右の子を空にし、r を繋ぐ。
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

    // split3 で得た {a, b, c} を戻す (a は右の子がない前提、c は左の子がない前提。
    // split3 の構成上、a は必ず cut_child で右を切った直後のノード、c は split() の
    // 戻り値でこちらも必ず左を切ってあるため、直接繋いでよい)
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

    // {切り離したノード, 残りの木} を返す
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
        T nxt = S::op(sm, Node::get_product(node));
        if (g(nxt)) {
            sm = nxt;
            return Node::get_size(node);
        }
        int res = max_right(node->children[0], sm, g);
        if (res != Node::get_size(node->children[0])) return res;
        T nxt2 = S::op(sm, node->value);
        if (!g(nxt2)) return res;
        sm = nxt2;
        ++res;
        return res + max_right(node->children[1], sm, g);
    }

    template <class G>
    static int min_left(node_ptr node, T &sm, G g) {
        if (!node) return 0;
        push(node);
        T nxt = S::op(Node::get_product(node), sm);
        if (g(nxt)) {
            sm = nxt;
            return Node::get_size(node);
        }
        int res = min_left(node->children[1], sm, g);
        if (res != Node::get_size(node->children[1])) return res;
        T nxt2 = S::op(node->value, sm);
        if (!g(nxt2)) return res;
        sm = nxt2;
        ++res;
        return res + min_left(node->children[0], sm, g);
    }
};
