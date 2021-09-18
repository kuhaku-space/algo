#include "_base.hpp"

struct link_cut_tree {
    struct node_t {
        node_t *pp, *lp, *rp;

        bool is_root() { return !pp || (pp->lp != this && pp->rp != this); }

        void rotr() {
            node_t *q = pp, *r = q->pp;
            if (q->lp = rp) rp->pp = q;
            rp = q;
            q->pp = this;
            if (pp = r) {
                if (r->lp == q) r->lp = this;
                if (r->rp == q) r->rp = this;
            }
        }

        void rotl() {
            node_t *q = pp, *r = q->pp;
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
                node_t *q = pp;
                if (q->is_root()) {
                    if (q->lp == this)
                        rotr();
                    else
                        rotl();
                } else {
                    node_t *r = q->pp;
                    if (r->lp == q) {
                        if (q->lp == this)
                            q->rotr(), rotr();
                        else
                            rotl(), rotr();

                    } else {
                        if (q->rp == this)
                            q->rotl(), rotl();
                        else
                            rotr(), rotl();
                    }
                }
            }
        }
    };

    node_t *expose(node_t *x) {
        node_t *rp = NULL;
        for (node_t *p = x; p; p = p->pp) {
            p->splay();
            p->rp = rp;
            rp = p;
        }
        x->splay();
        return x;
    }

    void cut(node_t *c) {
        expose(c);
        node_t *p = c->lp;
        c->lp = NULL;
        p->pp = NULL;
    }

    void link(node_t *c, node_t *p) {
        expose(c);
        expose(p);
        c->pp = p;
        p->rp = c;
    }
};
