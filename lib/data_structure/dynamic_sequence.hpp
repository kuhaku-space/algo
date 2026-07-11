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

        static int get_size(pointer node) { return !node ? 0 : node->size; }
        static int get_height(pointer node) { return !node ? 0 : node->height; }
        static T get_product(pointer node) { return !node ? M::id() : node->product; }

        Node(const T &v) : value(v), product(v), children{nullptr, nullptr}, size(1), height(1), reversed() {}
        Node(T &&v) : value(std::move(v)), product(value), children{nullptr, nullptr}, size(1), height(1), reversed() {}

        T value, product;
        pointer children[2];
        int size, height;
        bool reversed;

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

    void insert(int k, T val) { root = insert(root, k, val); }
    void push_front(const T &val) { root = merge(new Node(val), root); }
    void push_front(T &&val) { root = merge(new Node(std::move(val)), root); }
    void push_back(const T &val) { root = merge(root, new Node(val)); }
    void push_back(T &&val) { root = merge(root, new Node(std::move(val))); }

    void erase(int k) { root = erase(root, k); }
    void pop_front() { root = erase(root, 0); }
    void pop_back() { root = erase(root, Node::get_size(root) - 1); }

    T prod(int r) const { return prod(root, r); }
    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= Node::get_size(root));
        auto [pl, pr] = split(root, l);
        T res = prod(pr, r - l);
        root = merge(pl, pr);
        return res;
    }

    void reverse(int l, int r) {
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        if (qr) qr->reversed ^= true;
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
        auto [pl, pr] = split(root, r);
        auto [ql, qr] = split(pl, l);
        return std::make_tuple(DynamicSequence(ql), DynamicSequence(qr), DynamicSequence(pr));
    }

    void merge_left(DynamicSequence lhs) { root = merge(lhs.root, root); }
    void merge_right(DynamicSequence rhs) { root = merge(root, rhs.root); }

  private:
    node_ptr root;

    static void push(node_ptr node) {
        if (node && node->reversed) {
            std::swap(node->children[0], node->children[1]);
            if (node->children[0]) node->children[0]->reversed ^= true;
            if (node->children[1]) node->children[1]->reversed ^= true;
            node->reversed = false;
        }
    }

    static node_ptr update(node_ptr node) {
        push(node);
        node->size = Node::get_size(node->children[0]) + Node::get_size(node->children[1]) + 1;
        node->height = std::max(Node::get_height(node->children[0]), Node::get_height(node->children[1])) + 1;
        node->product =
            M::op(M::op(Node::get_product(node->children[0]), node->value), Node::get_product(node->children[1]));
        return node;
    }

    static int get_balance_factor(node_ptr node) {
        push(node);
        return Node::get_height(node->children[0]) - Node::get_height(node->children[1]);
    }

    // dir = 0: 右回転 (左の子を根に), dir = 1: 左回転 (右の子を根に)
    static node_ptr rotate(node_ptr node, int dir) {
        push(node);
        node_ptr pivot = node->children[dir];
        push(pivot);
        node->children[dir] = pivot->children[dir ^ 1];
        pivot->children[dir ^ 1] = node;
        update(node);
        return update(pivot);
    }

    static node_ptr rebalance(node_ptr node) {
        if (!node) return node;
        int bf = get_balance_factor(node);
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

    static node_ptr insert(node_ptr node, int k, T val) {
        if (!node) return new Node(val);
        push(node);
        int left_size = Node::get_size(node->children[0]);
        if (k <= left_size) node->children[0] = insert(node->children[0], k, val);
        else node->children[1] = insert(node->children[1], k - left_size - 1, val);
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

    static T prod(node_ptr node, int r) {
        assert(0 <= r && r <= Node::get_size(node));
        T res = M::id();
        while (r) {
            push(node);
            if (r == Node::get_size(node)) {
                res = M::op(res, Node::get_product(node));
                break;
            }
            int left_size = Node::get_size(node->children[0]);
            if (r < left_size) {
                node = node->children[0];
                continue;
            }
            res = M::op(res, Node::get_product(node->children[0]));
            r -= left_size;
            if (r) res = M::op(res, node->value), --r;

            node = node->children[1];
        }
        return res;
    }
};
