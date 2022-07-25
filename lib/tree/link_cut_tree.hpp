#include "template/template.hpp"

/**
 * @brief Link-Cut Tree
 *
 */
struct link_cut_tree {
  private:
    struct _node {
        using pointer = _node *;
        pointer pp, lp, rp;

        bool is_root() { return !pp || (pp->lp != this && pp->rp != this); }

        void rotr() {
            pointer q = pp, r = q->pp;
            if (q->lp = rp) rp->pp = q;
            rp = q;
            q->pp = this;
            if (pp = r) {
                if (r->lp == q) r->lp = this;
                if (r->rp == q) r->rp = this;
            }
        }

        void rotl() {
            pointer q = pp, r = q->pp;
            if (q->rp = lp) lp->pp = q;
            lp = q;
            q->pp = this;
            if (pp = r) {
                if (r->lp == q) r->lp = this;
                if (r->rp == q) r->rp = this;
            }
        }

        void splay() {
            while (!is_root()) {
                pointer q = pp;
                if (q->is_root()) {
                    if (q->lp == this) rotr();
                    else rotl();
                } else {
                    pointer r = q->pp;
                    if (r->lp == q) {
                        if (q->lp == this) q->rotr(), rotr();
                        else rotl(), rotr();

                    } else {
                        if (q->rp == this) q->rotl(), rotl();
                        else rotr(), rotl();
                    }
                }
            }
        }
    };

  public:
    using node_ptr = typename _node::pointer;

    node_ptr expose(node_ptr x) {
        node_ptr rp = nullptr;
        for (node_ptr p = x; p; p = p->pp) {
            p->splay();
            p->rp = rp;
            rp = p;
        }
        x->splay();
        return x;
    }

    void cut(node_ptr c) {
        this->expose(c);
        node_ptr p = c->lp;
        c->lp = nullptr;
        p->pp = nullptr;
    }

    void link(node_ptr c, node_ptr p) {
        this->expose(c);
        this->expose(p);
        c->pp = p;
        p->rp = c;
    }
};
