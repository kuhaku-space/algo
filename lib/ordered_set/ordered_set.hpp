#pragma once
#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

/// @brief 順序集合・多重集合（AVL 木）
/// @complexity 検索・更新・順位・区間和は $O(\log n)$
template <class T, bool Multi = false>
struct OrderedSet {
  private:
    struct Node {
        using pointer = Node *;

        T val, sum;
        int height, size;
        pointer left, right;

        constexpr Node(T _val) : val(_val), sum(_val), height(1), size(1), left(nullptr), right(nullptr) {}

        static constexpr T get_sum(pointer node) { return node == nullptr ? T() : node->sum; }
        static constexpr int get_height(pointer node) { return node == nullptr ? 0 : node->height; }
        static constexpr int get_size(pointer node) { return node == nullptr ? 0 : node->size; }
        static constexpr int get_balance_factor(pointer node) {
            return node == nullptr ? 0 : Node::get_height(node->left) - Node::get_height(node->right);
        }

        constexpr void recompute() {
            sum = Node::get_sum(left) + val + Node::get_sum(right);
            height = std::max(Node::get_height(left), Node::get_height(right)) + 1;
            size = Node::get_size(left) + Node::get_size(right) + 1;
        }

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

  public:
    /// @brief 内部ノード型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_type = Node;

    /// @brief 内部ノードへのpointer型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_ptr = typename Node::pointer;

    /// @brief 空集合を構築する
    /// @complexity $O(1)$
    constexpr OrderedSet() : root(nullptr) {}

    /// @brief 列vの要素から構築する
    /// @complexity $O(n\log n)$
    constexpr OrderedSet(std::vector<T> v) : root(nullptr) {
        std::sort(v.begin(), v.end());
        if constexpr (!Multi) v.erase(std::unique(v.begin(), v.end()), v.end());
        auto build = [&v](auto self, int l, int r) -> node_ptr {
            if (l == r) return nullptr;
            int m = (l + r) >> 1;
            auto node = new Node(v[m]);
            node->left = self(self, l, m);
            node->right = self(self, m + 1, r);
            node->recompute();
            return node;
        };
        root = build(build, 0, v.size());
    }

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return root == nullptr; }

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return Node::get_size(root); }

    /// @brief valを挿入する
    /// @complexity $O(\log n)$
    void insert(T val) {
        if constexpr (!Multi) {
            if (contains(val)) return;
        }
        root = insert(root, val);
    }

    /// @brief valを1個削除する
    /// @complexity $O(\log n)$
    void erase(T val) { root = erase(root, val); }

    /// @brief 最小要素を削除する
    /// @complexity $O(\log n)$
    void pop_front() { root = erase(root, front()); }

    /// @brief 最大要素を削除する
    /// @complexity $O(\log n)$
    void pop_back() { root = erase(root, back()); }

    /// @brief 最小要素を返す
    /// @complexity $O(\log n)$
    T front() {
        assert(root);
        node_ptr node = root;
        while (node->left) node = node->left;
        return node->val;
    }

    /// @brief 最大要素を返す
    /// @complexity $O(\log n)$
    T back() {
        assert(root);
        node_ptr node = root;
        while (node->right) node = node->right;
        return node->val;
    }

    /// @brief 0-indexedでk番目に小さい要素を返す
    /// @complexity $O(\log n)$
    T at(int k) const {
        assert(0 <= k && k < size());
        node_ptr node = root;
        while (true) {
            int c = Node::get_size(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else node = node->right, k -= c + 1;
        }
        return node->val;
    }

    /// @brief valの個数を返す
    /// @complexity $O(\log n)$
    int count(T val) const { return upper_bound(val) - lower_bound(val); }

    /// @brief valを含むか返す
    /// @complexity $O(\log n)$
    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) node = (val < node->val ? node->left : node->right);
        return node != nullptr;
    }

    /// @brief val未満の要素数を返す
    /// @complexity $O(\log n)$
    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) node = node->left;
            else res += Node::get_size(node->left) + 1, node = node->right;
        }
        return res;
    }

    /// @brief val以下の要素数を返す
    /// @complexity $O(\log n)$
    int upper_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (val < node->val) node = node->left;
            else res += Node::get_size(node->left) + 1, node = node->right;
        }
        return res;
    }

    /// @brief val以下で最大の要素を返す
    /// @complexity $O(\log n)$
    std::optional<T> floor(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(val < node->val)) res = node->val, node = node->right;
            else node = node->left;
        }
        return res;
    }

    /// @brief val以上で最小の要素を返す
    /// @complexity $O(\log n)$
    std::optional<T> ceil(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) res = node->val, node = node->left;
            else node = node->right;
        }
        return res;
    }

    /// @brief 小さい方からk個の総和を返す
    /// @complexity $O(\log n)$
    T prefix_sum(int k) const {
        assert(0 <= k && k <= size());
        if (k == size()) return Node::get_sum(root);
        T res{};
        node_ptr node = root;
        while (node && k) {
            int c = Node::get_size(node->left);
            if (k < c) {
                node = node->left;
            } else {
                res += Node::get_sum(node->left);
                if (k == c) break;
                res += node->val;
                node = node->right, k -= c + 1;
            }
        }
        return res;
    }

    /// @brief 大きい方からk個の総和を返す
    /// @complexity $O(\log n)$
    T suffix_sum(int k) const {
        assert(0 <= k && k <= size());
        if (k == size()) return Node::get_sum(root);
        T res{};
        node_ptr node = root;
        while (node && k) {
            int c = Node::get_size(node->right);
            if (k < c) {
                node = node->right;
            } else {
                res += Node::get_sum(node->right);
                if (k == c) break;
                res += node->val;
                node = node->left, k -= c + 1;
            }
        }
        return res;
    }

  private:
    node_ptr root;

    constexpr T min_val(node_ptr node) const {
        assert(node);
        while (node->left) node = node->left;
        return node->val;
    }

    constexpr node_ptr rotate_left(node_ptr node) {
        assert(node);
        node_ptr pivot = node->right;
        assert(pivot);
        node->right = pivot->left;
        pivot->left = node;
        node->recompute();
        pivot->recompute();
        return pivot;
    }

    constexpr node_ptr rotate_right(node_ptr node) {
        assert(node);
        node_ptr pivot = node->left;
        assert(pivot);
        node->left = pivot->right;
        pivot->right = node;
        node->recompute();
        pivot->recompute();
        return pivot;
    }

    constexpr node_ptr rotate_left_right(node_ptr node) {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
        return node;
    }

    constexpr node_ptr rotate_right_left(node_ptr node) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
        return node;
    }

    constexpr node_ptr rebalance(node_ptr node) {
        int bf = Node::get_balance_factor(node);
        if (bf < -1) {
            if (Node::get_balance_factor(node->right) >= 1) node = rotate_right_left(node);
            else node = rotate_left(node);
        } else if (bf > 1) {
            if (Node::get_balance_factor(node->left) <= -1) node = rotate_left_right(node);
            else node = rotate_right(node);
        } else {
            node->recompute();
        }
        return node;
    }

    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new Node(val);
        if (val < node->val) node->left = insert(node->left, val);
        else node->right = insert(node->right, val);
        return rebalance(node);
    }

    constexpr node_ptr erase(node_ptr node, T val) {
        if (node == nullptr) return nullptr;
        if (val < node->val) {
            node->left = erase(node->left, val);
        } else if (node->val < val) {
            node->right = erase(node->right, val);
        } else {
            if (node->right == nullptr) return node->left;
            else node->val = min_val(node->right), node->right = erase_min(node->right);
        }
        return rebalance(node);
    }

    constexpr node_ptr erase_min(node_ptr node) {
        if (node->left == nullptr) return node->right;
        node->left = erase_min(node->left);
        return rebalance(node);
    }
};
