#pragma once
#include "template/template.hpp"
#include "segtree/monoid.hpp"

/// @brief Link-Cut Tree
/// @complexity 構築は $O(n)$、link・cut・reroot・exposeは償却 $O(\log n)$
template <monoid M>
struct link_cut_tree {
  private:
    using T = typename M::value_type;

    struct node_t {
        using pointer = node_t *;

        constexpr node_t() : parent(), left(), right(), is_flip(), value(), total() {}
        constexpr node_t(const T &val) : parent(), left(), right(), is_flip(), value(val), total(val) {}
        constexpr node_t(T &&val) : parent(), left(), right(), is_flip(), value(val), total(val) {}

        constexpr T get_value() const { return value; }
        constexpr T get_total() const { return total; }

        constexpr bool is_root() { return !parent || (parent->left != this && parent->right != this); }

        void set(T val) {
            value = val;
            update();
        }
        void update() {
            total = value;
            if (left) total = M::op(left->total, total);
            if (right) total = M::op(total, right->total);
        }

        void flip() {
            is_flip = !is_flip;
            std::swap(left, right);
        }
        void propagate() {
            if (is_flip) {
                is_flip = false;
                if (left) left->flip();
                if (right) right->flip();
            }
        }
        void propagate_all() {
            if (!is_root()) parent->propagate_all();
            propagate();
        }

        void rotate() {
            bool is_right_child = (parent->right == this);
            pointer pa = parent;
            pointer ch = (is_right_child ? left : right);

            if (!pa->is_root()) {
                if (pa->parent->right == pa) pa->parent->right = this;
                else pa->parent->left = this;
            }
            parent = pa->parent;

            (is_right_child ? left : right) = pa;
            pa->parent = this;
            (!is_right_child ? pa->left : pa->right) = ch;
            if (ch) ch->parent = pa;

            pa->update();
            update();
        }
        void splay() {
            propagate_all();
            while (!is_root()) {
                if (!parent->is_root()) {
                    if ((parent->right == this) == (parent->parent->right == parent)) parent->rotate();
                    else rotate();
                }
                rotate();
            }
        }

        void expose() {
            splay();
            while (parent) {
                parent->splay();
                parent->right = this;
                rotate();
            }
            right = nullptr;
            update();
        }

        void make_root() {
            expose();
            flip();
        }

        void link(pointer v) {
            make_root();
            parent = v;
        }

        void cut() {
            expose();
            left->parent = nullptr;
            left = nullptr;
            update();
        }

      private:
        pointer parent, left, right;
        bool is_flip;
        T value, total;
    };

  public:
    /// @brief 内部ノード型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_type = node_t;

    /// @brief 内部ノードへのpointer型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_ptr = typename node_t::pointer;

    /// @brief n個の単位元頂点を構築する
    /// @complexity $O(n)$
    link_cut_tree(int n) : nodes(n, nullptr) {
        for (int i = 0; i < n; ++i) nodes[i] = new node_t();
    }

    /// @brief 頂点値vから構築する
    /// @complexity $O(n)$
    link_cut_tree(const std::vector<T> &v) : nodes(v.size(), nullptr) {
        for (int i = 0; i < (int)v.size(); ++i) nodes[i] = new node_t(v[i]);
    }

    /// @brief 頂点vの値をvalへ変更する
    /// @complexity 償却 $O(\log n)$
    void set(int v, T val) {
        nodes[v]->splay();
        nodes[v]->set(val);
    }

    /// @brief 頂点v自身の値を返す
    /// @complexity $O(1)$
    T get_value(int v) { return nodes[v]->get_value(); }

    /// @brief 現在の補助木でv以下の集約値を返す
    /// @complexity $O(1)$
    T get_total(int v) { return nodes[v]->get_total(); }

    /// @brief uとvを連結する
    /// @complexity 償却 $O(\log n)$
    void link(int u, int v) { nodes[u]->link(nodes[v]); }

    /// @brief 辺u-vを切断する
    /// @complexity 償却 $O(\log n)$
    void cut(int u, int v) {
        nodes[u]->make_root();
        nodes[v]->cut();
    }

    /// @brief vを親から切断する
    /// @complexity 償却 $O(\log n)$
    void cut(int v) { nodes[v]->cut(); }

    /// @brief vを補助木の根までsplayする
    /// @complexity 償却 $O(\log n)$
    void splay(int v) { nodes[v]->splay(); }

    /// @brief vを表現木の根にする
    /// @complexity 償却 $O(\log n)$
    void make_root(int v) { nodes[v]->make_root(); }

    /// @brief 根からvまでのpreferred pathを露出する
    /// @complexity 償却 $O(\log n)$
    void expose(int v) { nodes[v]->expose(); }

  private:
    std::vector<node_ptr> nodes;
};
