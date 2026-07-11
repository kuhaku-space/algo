#pragma once
#include <algorithm>
#include <cassert>
#include <optional>
#include <vector>

template <class T>
struct ordered_set {
  private:
    struct node_t {
        using pointer = node_t *;

        T val, sum;
        int height, size;
        pointer left, right;

        constexpr node_t(T _val) : val(_val), sum(_val), height(1), size(1), left(nullptr), right(nullptr) {}

        static constexpr T get_sum(pointer node) { return node == nullptr ? T() : node->sum; }
        static constexpr int get_height(pointer node) { return node == nullptr ? 0 : node->height; }
        static constexpr int get_size(pointer node) { return node == nullptr ? 0 : node->size; }
        static constexpr int get_balance_factor(pointer node) {
            return node == nullptr ? 0 : node_t::get_height(node->left) - node_t::get_height(node->right);
        }

        constexpr void recompute() {
            sum = node_t::get_sum(left) + val + node_t::get_sum(right);
            height = std::max(node_t::get_height(left), node_t::get_height(right)) + 1;
            size = node_t::get_size(left) + node_t::get_size(right) + 1;
        }

        // erase したノードは再利用しないため、確保のみ行うバンプアロケータで malloc 呼び出し回数を減らす
        static constexpr std::size_t chunk_size = 1 << 16;
        static inline std::vector<node_t *> chunks;
        static inline std::size_t chunk_pos = 0;

        static void *operator new(std::size_t) {
            if (chunks.empty() || chunk_pos == chunk_size) {
                chunks.push_back(static_cast<node_t *>(::operator new(chunk_size * sizeof(node_t))));
                chunk_pos = 0;
            }
            return chunks.back() + (chunk_pos++);
        }
        static void operator delete(void *) noexcept {}
    };

  public:
    using node_type = node_t;
    using node_ptr = typename node_t::pointer;

    constexpr ordered_set() : root(nullptr) {}
    constexpr ordered_set(const std::vector<T> &v) : root(nullptr) {
        auto build = [&v](auto self, int l, int r) -> node_ptr {
            if (l == r) return nullptr;
            int m = (l + r) >> 1;
            auto node = new node_t(v[m]);
            node->left = self(self, l, m);
            node->right = self(self, m + 1, r);
            node->recompute();
            return node;
        };
        root = build(build, 0, v.size());
    }

    constexpr bool empty() const { return root == nullptr; }
    constexpr int size() const { return node_t::get_size(root); }

    void insert(T val) { root = insert(root, val); }

    void erase(T val) { root = erase(root, val); }

    void pop_front() { root = erase(root, front()); }
    void pop_back() { root = erase(root, back()); }

    T front() {
        assert(root);
        node_ptr node = root;
        while (node->left) node = node->left;
        return node->val;
    }
    T back() {
        assert(root);
        node_ptr node = root;
        while (node->right) node = node->right;
        return node->val;
    }

    T at(int k) const {
        assert(0 <= k && k < size());
        node_ptr node = root;
        while (true) {
            int c = node_t::get_size(node->left);
            if (c == k) break;
            if (k < c) node = node->left;
            else node = node->right, k -= c + 1;
        }
        return node->val;
    }

    int count(T val) const { return upper_bound(val) - lower_bound(val); }

    bool contains(T val) const {
        node_ptr node = root;
        while (node && node->val != val) node = (val < node->val ? node->left : node->right);
        return node != nullptr;
    }

    int lower_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) node = node->left;
            else res += node_t::get_size(node->left) + 1, node = node->right;
        }
        return res;
    }

    int upper_bound(T val) const {
        int res = 0;
        node_ptr node = root;
        while (node) {
            if (val < node->val) node = node->left;
            else res += node_t::get_size(node->left) + 1, node = node->right;
        }
        return res;
    }

    std::optional<T> floor(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(val < node->val)) res = node->val, node = node->right;
            else node = node->left;
        }
        return res;
    }

    std::optional<T> ceil(T val) const {
        std::optional<T> res = std::nullopt;
        node_ptr node = root;
        while (node) {
            if (!(node->val < val)) res = node->val, node = node->left;
            else node = node->right;
        }
        return res;
    }

    T prefix_sum(int k) const {
        assert(0 <= k && k <= size());
        if (k == size()) return node_t::get_sum(root);
        T res{};
        node_ptr node = root;
        while (node && k) {
            int c = node_t::get_size(node->left);
            if (k < c) {
                node = node->left;
            } else {
                res += node_t::get_sum(node->left);
                if (k == c) break;
                res += node->val;
                node = node->right, k -= c + 1;
            }
        }
        return res;
    }

    T suffix_sum(int k) const {
        assert(0 <= k && k <= size());
        if (k == size()) return node_t::get_sum(root);
        T res{};
        node_ptr node = root;
        while (node && k) {
            int c = node_t::get_size(node->right);
            if (k < c) {
                node = node->right;
            } else {
                res += node_t::get_sum(node->right);
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
        int bf = node_type::get_balance_factor(node);
        if (bf < -1) {
            if (node_type::get_balance_factor(node->right) >= 1) node = rotate_right_left(node);
            else node = rotate_left(node);
        } else if (bf > 1) {
            if (node_type::get_balance_factor(node->left) <= -1) node = rotate_left_right(node);
            else node = rotate_right(node);
        } else {
            node->recompute();
        }
        return node;
    }

    constexpr node_ptr insert(node_ptr node, T val) {
        if (node == nullptr) return new node_t(val);
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
