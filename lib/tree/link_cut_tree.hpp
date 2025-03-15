#pragma once
#include "segtree/monoid.hpp"
#include "template/template.hpp"

/**
 * @brief Link-Cut Tree
 *
 * @tparam M 可換モノイド
 */
template <class M>
struct link_cut_tree {
  private:
    using T = typename M::value_type;

    struct _node {
        using pointer = _node *;

        pointer pp, lp, rp;
        bool flip;
        T val, total;

        constexpr bool is_root() { return !pp || (pp->lp != this && pp->rp != this); }

        void set(T val) {
            this->val = val;
            this->update();
        }
        void update() {
            this->total = val;
            if (this->lp) this->total = M::op(this->lp->total, this->total);
            if (this->rp) this->total = M::op(this->total, this->rp->total);
        }

        void do_flip() {
            this->flip = !this->flip;
            std::swap(this->lp, this->rp);
        }
        void propagate() {
            if (this->flip) {
                this->flip = false;
                if (this->lp) this->lp->do_flip();
                if (this->rp) this->rp->do_flip();
            }
        }
        void propagate_all() {
            if (!this->is_root()) this->pp->propagate_all();
            this->propagate();
        }

        void rot() {
            int x = (this->pp->rp == this);
            pointer pa = this->pp;
            pointer ch = (x ? this->lp : this->rp);

            if (!pa->is_root()) {
                if (pa->pp->rp == pa) pa->pp->rp = this;
                else pa->pp->lp = this;
            }
            this->pp = pa->pp;

            (x ? this->lp : this->rp) = pa;
            pa->pp = this;
            (!x ? pa->lp : pa->rp) = ch;
            if (ch) ch->pp = pa;

            pa->update();
            this->update();
        }
        void splay() {
            this->propagate_all();
            while (!this->is_root()) {
                if (!this->pp->is_root()) {
                    if ((this->pp->rp == this) == (this->pp->pp->rp == pp)) {
                        this->pp->rot();
                    } else {
                        this->rot();
                    }
                }
                this->rot();
            }
        }

        void expose() {
            this->splay();
            while (this->pp) {
                this->pp->splay();
                this->pp->rp = this;
                this->rot();
            }
            this->rp = nullptr;
            this->update();
        }

        void make_root() {
            this->expose();
            this->do_flip();
        }

        void link(pointer v) {
            this->make_root();
            this->pp = v;
        }

        void cut() {
            this->expose();
            this->lp->pp = nullptr;
            this->lp = nullptr;
            this->update();
        }
    };

  public:
    using node_type = _node;
    using node_ptr = typename _node::pointer;

    link_cut_tree(int n) : nodes(n, nullptr) {
        for (int i = 0; i < n; ++i) { this->nodes[i] = new _node(); }
    }

    void set(int v, T val) {
        this->nodes[v]->splay();
        this->nodes[v]->set(val);
    }
    T get_val(int v) { return this->nodes[v]->val; }
    T get_total(int v) { return this->nodes[v]->total; }
    void link(int u, int v) { this->nodes[u]->link(nodes[v]); }
    void cut(int u, int v) {
        this->nodes[u]->make_root();
        this->nodes[v]->cut();
    }
    void cut(int v) { this->nodes[v]->cut(); }
    void splay(int v) { this->nodes[v]->splay(); }
    void make_root(int v) { this->nodes[v]->make_root(); }
    void expose(int v) { this->nodes[v]->expose(); }

  private:
    std::vector<node_ptr> nodes;
};
