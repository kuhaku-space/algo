#pragma once
#include <cassert>
#include <map>
#include <utility>
#include <vector>
#include "segtree/monoid.hpp"

// Euler Tour Tree
template <class M>
struct euler_tour_tree {
    using T = typename M::value_type;

    struct node_t {
        int u, v;
        T val, sum;
        int sz;
        node_t *par, *l, *r;

        node_t(int _u, int _v, const T &_val = M::id())
            : u(_u), v(_v), val(_val), sum(_val), sz(u == v ? 1 : 0), par(nullptr), l(nullptr), r(nullptr) {}
    };

    int n;
    std::vector<node_t *> vertex_node;
    std::map<std::pair<int, int>, node_t *> edge_node;

    euler_tour_tree(int _n) : n(_n) {
        vertex_node.resize(n, nullptr);
        for (int i = 0; i < n; ++i) vertex_node[i] = new node_t(i, i);
    }

    euler_tour_tree(const std::vector<T> &v) : n(v.size()) {
        vertex_node.resize(n, nullptr);
        for (int i = 0; i < n; ++i) vertex_node[i] = new node_t(i, i, v[i]);
    }

    ~euler_tour_tree() {
        for (auto nd : vertex_node) delete nd;
        for (auto &p : edge_node) delete p.second;
    }

    void link(int u, int v) {
        reroot(u);
        reroot(v);
        node_t *uv = new node_t(u, v);
        node_t *vu = new node_t(v, u);
        edge_node[{u, v}] = uv;
        edge_node[{v, u}] = vu;

        node_t *tu = vertex_node[u];
        node_t *tv = vertex_node[v];
        splay(tu);
        splay(tv);
        join(tu, join(uv, join(tv, vu)));
    }

    void cut(int u, int v) {
        node_t *uv = edge_node[{u, v}];
        node_t *vu = edge_node[{v, u}];
        edge_node.erase({u, v});
        edge_node.erase({v, u});

        reroot(u);

        splay(vu);
        node_t *C = vu->r;
        node_t *AB_uv = vu->l;
        if (C) C->par = nullptr;
        if (AB_uv) AB_uv->par = nullptr;
        vu->l = vu->r = nullptr;
        update(vu);

        splay(uv);
        node_t *B = uv->r;
        node_t *A = uv->l;
        if (B) B->par = nullptr;
        if (A) A->par = nullptr;
        uv->l = uv->r = nullptr;
        update(uv);

        join(A, C);

        delete uv;
        delete vu;
    }

    bool same(int u, int v) { return get_root(vertex_node[u]) == get_root(vertex_node[v]); }

    void set(int u, const T &val) {
        node_t *nd = vertex_node[u];
        splay(nd);
        nd->val = val;
        update(nd);
    }

    T get(int u) {
        node_t *nd = vertex_node[u];
        splay(nd);
        return nd->val;
    }

    T get_subtree(int v, int p = -1) {
        if (p == -1 || p == v) {
            node_t *nd = vertex_node[v];
            splay(nd);
            return nd->sum;
        }

        auto it_pv = edge_node.find({p, v});
        assert(it_pv != edge_node.end());
        node_t *pv = it_pv->second;
        node_t *vp = edge_node[{v, p}];

        reroot(p);

        splay(vp);
        node_t *C = vp->r;
        node_t *AB_pv = vp->l;
        if (C) C->par = nullptr;
        if (AB_pv) AB_pv->par = nullptr;
        vp->l = vp->r = nullptr;
        update(vp);

        splay(pv);
        node_t *B = pv->r;
        node_t *A = pv->l;
        if (B) B->par = nullptr;
        if (A) A->par = nullptr;
        pv->l = pv->r = nullptr;
        update(pv);

        T res = B ? B->sum : M::id();

        pv->l = A;
        if (A) A->par = pv;
        pv->r = B;
        if (B) B->par = pv;
        update(pv);

        vp->l = pv;
        pv->par = vp;
        vp->r = C;
        if (C) C->par = vp;
        update(vp);

        return res;
    }

    int get_size(int v, int p = -1) {
        if (p == -1 || p == v) {
            node_t *nd = vertex_node[v];
            splay(nd);
            return nd->sz;
        }
        auto it_pv = edge_node.find({p, v});
        assert(it_pv != edge_node.end());
        node_t *pv = it_pv->second;
        node_t *vp = edge_node[{v, p}];

        reroot(p);

        splay(vp);
        node_t *C = vp->r;
        node_t *AB_pv = vp->l;
        if (C) C->par = nullptr;
        if (AB_pv) AB_pv->par = nullptr;
        vp->l = vp->r = nullptr;
        update(vp);

        splay(pv);
        node_t *B = pv->r;
        node_t *A = pv->l;
        if (B) B->par = nullptr;
        if (A) A->par = nullptr;
        pv->l = pv->r = nullptr;
        update(pv);

        int res = B ? B->sz : 0;

        pv->l = A;
        if (A) A->par = pv;
        pv->r = B;
        if (B) B->par = pv;
        update(pv);

        vp->l = pv;
        pv->par = vp;
        vp->r = C;
        if (C) C->par = vp;
        update(vp);

        return res;
    }

  private:
    bool is_root(node_t *t) { return !t->par; }

    void update(node_t *t) {
        if (!t) return;
        t->sum = t->val;
        t->sz = (t->u == t->v) ? 1 : 0;
        if (t->l) {
            t->sum = M::op(t->l->sum, t->sum);
            t->sz += t->l->sz;
        }
        if (t->r) {
            t->sum = M::op(t->sum, t->r->sum);
            t->sz += t->r->sz;
        }
    }

    void rotate(node_t *t) {
        node_t *p = t->par;
        node_t *pp = p->par;
        if (p->l == t) {
            p->l = t->r;
            if (t->r) t->r->par = p;
            t->r = p;
        } else {
            p->r = t->l;
            if (t->l) t->l->par = p;
            t->l = p;
        }
        p->par = t;
        t->par = pp;
        if (pp) {
            if (pp->l == p) pp->l = t;
            else pp->r = t;
        }
        update(p);
        update(t);
    }

    void splay(node_t *t) {
        if (!t) return;
        while (!is_root(t)) {
            node_t *p = t->par;
            if (!is_root(p)) {
                node_t *pp = p->par;
                if ((pp->l == p) == (p->l == t)) rotate(p);
                else rotate(t);
            }
            rotate(t);
        }
    }

    node_t *join(node_t *l, node_t *r) {
        if (!l) return r;
        if (!r) return l;
        while (l->r) l = l->r;
        splay(l);
        l->r = r;
        r->par = l;
        update(l);
        return l;
    }

    void reroot(int v) {
        node_t *nd = vertex_node[v];
        splay(nd);
        node_t *l = nd->l;
        if (l) {
            l->par = nullptr;
            nd->l = nullptr;
            update(nd);
            join(nd, l);
        }
    }

    node_t *get_root(node_t *t) {
        if (!t) return nullptr;
        splay(t);
        while (t->l) t = t->l;
        splay(t);
        return t;
    }
};
