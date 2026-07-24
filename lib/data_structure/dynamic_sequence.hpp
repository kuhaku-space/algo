#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 動的配列（スプレー木、反転可能、遅延伝播対応）
/// @details 親ポインタを持つ反復版 splay で根に運んだノードを起点に split/merge を構成する
///          （amortized O(log n)）。全ての操作（読み取り専用のクエリも含む）で対象位置を
///          根まで splay する。AVL 版（join-based framework）と比較し、reverse/apply のような
///          split して戻す操作の再結合コストが軽いためこちらを採用している。
/// @tparam S データのモノイド
/// @tparam F 作用素モノイド（op が作用素の合成、f が値への作用）。`void` なら遅延伝播なし
///           （区間 apply は提供しない）。
/// @note `void` は内部で `std::monostate` に正規化し、本体を 1 つに保つ。
template <class S, class F = void>
requires monoid<S> && (std::is_void_v<F> || (monoid<F> && acts_on<F, typename S::value_type>))
struct DynamicSequence {
  private:
    using T = typename S::value_type;
    static constexpr bool use_lazy = !std::is_void_v<F>;
    struct void_monoid {
        using value_type = std::monostate;
    };
    using U = typename std::conditional_t<use_lazy, F, void_monoid>::value_type;

    struct Node {
        using pointer = Node *;

        static int get_size(pointer node) { return !node ? 0 : node->size; }
        static T get_product(pointer node) { return !node ? S::id() : node->product; }

        Node(const T &v) : value(v), product(v), children{nullptr, nullptr}, parent(nullptr), size(1), reversed() {
            if constexpr (use_lazy) {
                lazy = F::id();
                has_lazy = false;
            }
        }
        Node(T &&v)
            : value(std::move(v)), product(value), children{nullptr, nullptr}, parent(nullptr), size(1), reversed() {
            if constexpr (use_lazy) {
                lazy = F::id();
                has_lazy = false;
            }
        }

        T value, product;
        [[no_unique_address]] std::conditional_t<use_lazy, U, std::monostate> lazy;
        pointer children[2];
        pointer parent;
        int size;
        bool reversed;
        [[no_unique_address]] std::conditional_t<use_lazy, bool, std::monostate> has_lazy;

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
    /// @brief 空の動的配列を構築する
    /// @complexity $O(1)$
    DynamicSequence() : root(nullptr) {}

    /// @brief 内部木から動的配列を構築する
    /// @complexity $O(1)$
    DynamicSequence(node_ptr p) : root(p) {}

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    int size() const { return Node::get_size(root); }

    /// @brief k番目の値を返す
    /// @complexity 償却 $O(\log n)$
    T get(int k) {
        assert(k < Node::get_size(root));
        root = access(root, k);
        return root->value;
    }

    /// @brief k番目の値を設定する
    /// @complexity 償却 $O(\log n)$
    void set(int k, T val) {
        assert(k < Node::get_size(root));
        root = access(root, k);
        root->value = val;
        update(root);
    }

    /// @brief k番目へ値を挿入する
    /// @complexity 償却 $O(\log n)$
    void insert(int k, const T &val) { root = insert(root, k, new Node(val)); }

    /// @brief k番目へ値をムーブして挿入する
    /// @complexity 償却 $O(\log n)$
    void insert(int k, T &&val) { root = insert(root, k, new Node(std::move(val))); }

    /// @brief k番目へ値を直接構築して挿入する
    /// @complexity 償却 $O(\log n)$
    template <class... Args>
    void emplace(int k, Args &&...args) {
        root = insert(root, k, new Node(T(std::forward<Args>(args)...)));
    }
    /// @brief 先頭へ値を追加する
    /// @complexity 償却 $O(\log n)$
    void push_front(const T &val) { root = merge(new Node(val), root); }

    /// @brief 先頭へ値をムーブして追加する
    /// @complexity 償却 $O(\log n)$
    void push_front(T &&val) { root = merge(new Node(std::move(val)), root); }

    /// @brief 末尾へ値を追加する
    /// @complexity 償却 $O(\log n)$
    void push_back(const T &val) { root = merge(root, new Node(val)); }

    /// @brief 末尾へ値をムーブして追加する
    /// @complexity 償却 $O(\log n)$
    void push_back(T &&val) { root = merge(root, new Node(std::move(val))); }

    /// @brief k番目の値を削除する
    /// @complexity 償却 $O(\log n)$
    void erase(int k) {
        assert(k < Node::get_size(root));
        auto [erased, rest] = erase(root, k);
        (void)erased;
        root = rest;
    }
    /// @brief 先頭の値を削除する
    /// @complexity 償却 $O(\log n)$
    void pop_front() { erase(0); }

    /// @brief 末尾の値を削除する
    /// @complexity 償却 $O(\log n)$
    void pop_back() { erase(Node::get_size(root) - 1); }

    /// @brief 接頭辞のモノイド積を返す
    /// @complexity 償却 $O(\log n)$
    T prod(int r) { return prod(0, r); }

    /// @brief 半開区間のモノイド積を返す
    /// @complexity 償却 $O(\log n)$
    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        if (l == r) return S::id();
        auto [a, b, c] = split3(root, l, r);
        T res = Node::get_product(b);
        root = merge3(a, b, c);
        return res;
    }

    /// @brief 半開区間を反転する
    /// @complexity 償却 $O(\log n)$
    void reverse(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        if (b) b->reversed ^= true;
        root = merge3(a, b, c);
    }

    /// @brief v[p] に f を作用させる
    /// @complexity 償却 $O(\log n)$
    void apply(int p, U f)
    requires use_lazy
    {
        apply(p, p + 1, f);
    }
    /// @brief v[l ... r-1] に f を作用させる
    /// @complexity 償却 $O(\log n)$
    void apply(int l, int r, U f)
    requires use_lazy
    {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        if (l == r) return;
        auto [a, b, c] = split3(root, l, r);
        all_apply(b, f);
        root = merge3(a, b, c);
    }

    /// @brief prod(i) < key <= prod(i + 1) となる i（すべての i で prod(i) < key なら size()）
    /// @complexity 償却 $O(\log n)$
    int lower_bound(T key) {
        if (!(S::id() < key)) return 0;
        return max_right([&key](const T &x) { return x < key; });
    }

    /// @brief g(prod(0,r))が真となる最大のrを返す
    /// @complexity 償却 $O(\log n)$
    template <class G>
    int max_right(G g) {
        return max_right(0, g);
    }
    /// @brief g(prod(l,r))が真となる最大のrを返す
    /// @complexity 償却 $O(\log n)$
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

    /// @brief g(prod(l,n))が真となる最小のlを返す
    /// @complexity 償却 $O(\log n)$
    template <class G>
    int min_left(G g) {
        return min_left(Node::get_size(root), g);
    }
    /// @brief g(prod(l,r))が真となる最小のlを返す
    /// @complexity 償却 $O(\log n)$
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

    /// @brief k番目で2つの配列へ分割する
    /// @complexity 償却 $O(\log n)$
    std::pair<DynamicSequence, DynamicSequence> split(int k) {
        auto [pl, pr] = split(root, k);
        return std::make_pair(DynamicSequence(pl), DynamicSequence(pr));
    }
    /// @brief lとrで3つの配列へ分割する
    /// @complexity 償却 $O(\log n)$
    std::tuple<DynamicSequence, DynamicSequence, DynamicSequence> split(int l, int r) {
        auto [a, b, c] = split3(root, l, r);
        return std::make_tuple(DynamicSequence(a), DynamicSequence(b), DynamicSequence(c));
    }

    /// @brief 別の配列を先頭へ連結する
    /// @complexity 償却 $O(\log n)$
    void merge_left(DynamicSequence lhs) { root = merge(lhs.root, root); }

    /// @brief 別の配列を末尾へ連結する
    /// @complexity 償却 $O(\log n)$
    void merge_right(DynamicSequence rhs) { root = merge(root, rhs.root); }

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
        if constexpr (use_lazy) {
            if (node->has_lazy) {
                all_apply(node->children[0], node->lazy);
                all_apply(node->children[1], node->lazy);
                node->has_lazy = false;
            }
        }
    }

    static node_ptr update(node_ptr node) {
        node->size = Node::get_size(node->children[0]) + Node::get_size(node->children[1]) + 1;
        node->product =
            S::op(S::op(Node::get_product(node->children[0]), node->value), Node::get_product(node->children[1]));
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
