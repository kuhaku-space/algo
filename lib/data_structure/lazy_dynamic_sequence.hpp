#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <tuple>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

/// @brief 遅延伝播動的配列（AVL 木、反転可能）
/// @details split/merge は join-based framework（split_last + join）で構成し、AVL の高さ制約により
///          各操作 O(log n) worst-case を保証する。
/// @tparam S データのモノイド
/// @tparam F 作用素モノイド（op が作用素の合成、f が値への作用）
template <class S, class F>
requires monoid<S> && monoid<F> && acts_on<F, typename S::value_type>
struct LazyDynamicSequence {
  private:
    using T = typename S::value_type;
    using U = typename F::value_type;

    struct Node {
        using pointer = Node *;

        static int get_size(pointer node) { return !node ? 0 : node->size; }
        static int get_height(pointer node) { return !node ? 0 : node->height; }
        static T get_product(pointer node) { return !node ? S::id() : node->product; }

        Node(const T &v)
            : value(v), product(v), lazy(F::id()), children{nullptr, nullptr}, size(1), height(1), reversed(),
              has_lazy() {}
        Node(T &&v)
            : value(std::move(v)), product(value), lazy(F::id()), children{nullptr, nullptr}, size(1), height(1),
              reversed(), has_lazy() {}

        T value, product;
        U lazy;
        pointer children[2];
        int size, height;
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
    LazyDynamicSequence() : root(nullptr) {}
    LazyDynamicSequence(node_ptr p) : root(p) {}

    int size() const { return Node::get_size(root); }

    T get(int k) {
        assert(k < Node::get_size(root));
        node_ptr node = root;
        while (true) {
            push(node);
            int left_size = Node::get_size(node->children[0]);
            if (left_size == k) break;
            if (k < left_size) node = node->children[0];
            else node = node->children[1], k -= left_size + 1;
        }
        return node->value;
    }

    void set(int k, T val) {
        assert(k < Node::get_size(root));
        node_ptr node = root;
        std::vector<node_ptr> nodes;
        while (true) {
            push(node);
            nodes.emplace_back(node);
            int left_size = Node::get_size(node->children[0]);
            if (left_size == k) break;
            if (k < left_size) node = node->children[0];
            else node = node->children[1], k -= left_size + 1;
        }
        node->value = val;
        std::reverse(nodes.begin(), nodes.end());
        for (auto anc : nodes) update(anc);
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

    void erase(int k) { root = erase(root, k); }
    void pop_front() { root = erase(root, 0); }
    void pop_back() { root = erase(root, Node::get_size(root) - 1); }

    T prod(int r) const { return prod(root, 0, r); }
    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        return prod(root, l, r);
    }

    void reverse(int l, int r) {
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        if (qr) qr->reversed ^= true;
        root = merge(ql, qr);
        root = merge(root, pr);
    }

    void apply(int p, U f) { apply(p, p + 1, f); }
    void apply(int l, int r, U f) {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        if (l == r) return;
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        all_apply(qr, f);
        root = merge(ql, qr);
        root = merge(root, pr);
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

    std::pair<LazyDynamicSequence, LazyDynamicSequence> split(int k) {
        auto [pl, pr] = split(root, k);
        return std::make_pair(LazyDynamicSequence(pl), LazyDynamicSequence(pr));
    }
    std::tuple<LazyDynamicSequence, LazyDynamicSequence, LazyDynamicSequence> split(int l, int r) {
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        return std::make_tuple(LazyDynamicSequence(ql), LazyDynamicSequence(qr), LazyDynamicSequence(pr));
    }

    void merge_left(LazyDynamicSequence lhs) { root = merge(lhs.root, root); }
    void merge_right(LazyDynamicSequence rhs) { root = merge(root, rhs.root); }

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

    // 呼び出し元が既に push(node) 済みであることが前提（node 自身の reversed/lazy は解決済み）
    static node_ptr update(node_ptr node) {
        node->size = Node::get_size(node->children[0]) + Node::get_size(node->children[1]) + 1;
        node->height = std::max(Node::get_height(node->children[0]), Node::get_height(node->children[1])) + 1;
        node->product =
            S::op(S::op(Node::get_product(node->children[0]), node->value), Node::get_product(node->children[1]));
        return node;
    }

    static int get_balance_factor(node_ptr node) {
        push(node);
        return Node::get_height(node->children[0]) - Node::get_height(node->children[1]);
    }

    // dir = 0: 右回転 (左の子を根に), dir = 1: 左回転 (右の子を根に)
    // rebalance からのみ呼ばれ、node は get_balance_factor により push 済みが前提
    static node_ptr rotate(node_ptr node, int dir) {
        node_ptr pivot = node->children[dir];
        push(pivot);
        node->children[dir] = pivot->children[dir ^ 1];
        pivot->children[dir ^ 1] = node;
        update(node);
        return update(pivot);
    }

    // node は呼び出し元で push 済みが前提（get_balance_factor と違い push しない）
    static node_ptr rebalance(node_ptr node) {
        if (!node) return node;
        int bf = Node::get_height(node->children[0]) - Node::get_height(node->children[1]);
        if (bf == 2) {
            if (get_balance_factor(node->children[0]) < 0) node->children[0] = rotate(node->children[0], 1);
            return rotate(node, 0);
        } else if (bf == -2) {
            if (get_balance_factor(node->children[1]) > 0) node->children[1] = rotate(node->children[1], 0);
            return rotate(node, 1);
        }
        return node;
    }

    // mid を根、l と r をその子として結合する (join-based framework)
    static node_ptr join(node_ptr l, node_ptr mid, node_ptr r) {
        if (Node::get_height(l) > Node::get_height(r) + 1) {
            push(l);
            l->children[1] = join(l->children[1], mid, r);
            return rebalance(update(l));
        }
        if (Node::get_height(r) > Node::get_height(l) + 1) {
            push(r);
            r->children[0] = join(l, mid, r->children[0]);
            return rebalance(update(r));
        }
        mid->children[0] = l;
        mid->children[1] = r;
        return update(mid);
    }

    // node の最右ノードを切り離し {残りの木, 切り離したノード} を返す
    static std::pair<node_ptr, node_ptr> split_last(node_ptr node) {
        push(node);
        if (!node->children[1]) {
            node_ptr rest = node->children[0];
            node->children[0] = nullptr;
            return {rest, update(node)};
        }
        auto [rest, last] = split_last(node->children[1]);
        node->children[1] = rest;
        return {rebalance(update(node)), last};
    }

    static node_ptr merge(node_ptr l, node_ptr r) {
        if (!l || !r) return !l ? r : l;
        auto [rest, mid] = split_last(l);
        return join(rest, mid, r);
    }

    static std::pair<node_ptr, node_ptr> split(node_ptr node, int k) {
        if (!node) return std::make_pair<node_ptr, node_ptr>(nullptr, nullptr);
        push(node);
        int left_size = Node::get_size(node->children[0]);
        if (k <= left_size) {
            node_ptr old_right = node->children[1];
            auto [sub_l, sub_r] = split(node->children[0], k);
            node_ptr merged_r = join(sub_r, node, old_right);
            return std::make_pair(sub_l, merged_r);
        } else {
            node_ptr old_left = node->children[0];
            auto [sub_l, sub_r] = split(node->children[1], k - left_size - 1);
            node_ptr merged_l = join(old_left, node, sub_l);
            return std::make_pair(merged_l, sub_r);
        }
    }

    static node_ptr insert(node_ptr node, int k, node_ptr leaf) {
        if (!node) return leaf;
        push(node);
        int left_size = Node::get_size(node->children[0]);
        if (k <= left_size) node->children[0] = insert(node->children[0], k, leaf);
        else node->children[1] = insert(node->children[1], k - left_size - 1, leaf);
        return rebalance(update(node));
    }

    static node_ptr erase(node_ptr node, int k) {
        push(node);
        int left_size = Node::get_size(node->children[0]);
        if (k == left_size) return merge(node->children[0], node->children[1]);
        if (k < left_size) node->children[0] = erase(node->children[0], k);
        else node->children[1] = erase(node->children[1], k - left_size - 1);
        return rebalance(update(node));
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

    // node を根とする部分木のうち [l, r) にあたる範囲の積。木を一切再構成しない読み取り専用の走査。
    static T prod(node_ptr node, int l, int r) {
        if (!node || r <= 0 || l >= node->size) return S::id();
        if (l <= 0 && node->size <= r) return node->product;
        push(node);
        int left_size = Node::get_size(node->children[0]);
        T res = S::id();
        if (l < left_size) res = prod(node->children[0], l, r);
        if (l <= left_size && left_size < r) res = S::op(res, node->value);
        if (r > left_size + 1) res = S::op(res, prod(node->children[1], l - left_size - 1, r - left_size - 1));
        return res;
    }
};
