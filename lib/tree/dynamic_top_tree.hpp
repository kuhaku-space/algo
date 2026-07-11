#pragma once
#include <cstddef>
#include <utility>
#include <vector>

/// @brief Dynamic Top Tree（Link/Cut/Evert に対応した全方位木 DP）
/// @details LCT の compress パス（splay 木）に加え、各頂点にぶら下がる軽辺
///          （rake 対象の部分木）を別の splay 木で束ねて expose のたびに
///          O(log n) 償却で繋ぎ替える。evert によるパス反転に対応するため、
///          パス集約を正方向 sum・逆方向 mus の 2 本立てで保持する（compress
///          が非可換なため、反転を高速に行うにはこの複製が必要）。
///          TreeDP のインターフェースは static_top_tree_dp と共通：
///          `Path vertex(int u)` / `Path add_vertex(Path d, Light l)` /
///          `Light add_edge(Path d)` / `Light rake(Light l, Light r)` /
///          `Path compress(Path p, Path c)`。
template <class TreeDP>
struct DynamicTopTree {
    using Path = typename TreeDP::Path;
    using Light = typename TreeDP::Light;

    DynamicTopTree() = default;
    explicit DynamicTopTree(int n, const TreeDP &_dp = TreeDP()) : dp(_dp), nodes(n) {
        for (int i = 0; i < n; ++i) nodes[i].id = i;
        for (int i = 0; i < n; ++i) pull(&nodes[i]);
    }

    /// @brief c を子、p を親として連結する（内部で c を自身の根に evert してから繋ぐ）
    void link(int c, int p) {
        Node *pc = &nodes[c], *pp = &nodes[p];
        evert(c);
        expose(pp);
        expose(pc);
        pc->p = pp;
        pp->r = pc;
        pull(pp);
    }

    /// @brief c を親から切り離す
    void cut(int c) {
        Node *pc = &nodes[c];
        expose(pc);
        Node *l = pc->l;
        pc->l = nullptr;
        l->p = nullptr;
        pull(pc);
    }

    /// @brief 辺 (u, v) を切り離す
    void cut(int u, int v) {
        evert(u);
        cut(v);
    }

    /// @brief u を全体の根にする
    void evert(int u) {
        Node *t = &nodes[u];
        expose(t);
        toggle(t);
        push(t);
    }

    /// @brief 頂点 u の情報が変化した後に呼び、集約を再計算する
    void update(int u) {
        Node *t = &nodes[u];
        expose(t);
        pull(t);
    }

    /// @brief u を根としたときの木全体の集約値
    Path query(int u) {
        evert(u);
        return nodes[u].sum;
    }

    /// @brief root を根としたときの、u を根とする部分木の集約値
    Path query_subtree(int root, int u) {
        evert(root);
        Node *t = &nodes[u];
        expose(t);
        Node *l = t->l;
        t->l = nullptr;
        pull(t);
        Path res = t->sum;
        t->l = l;
        pull(t);
        return res;
    }

  private:
    struct LightNode {
        LightNode *l, *r, *p;
        Light key, sum;

        explicit LightNode(const Light &v) : l(), r(), p(), key(v), sum(v) {}

        static constexpr std::size_t chunk_size = 1 << 16;
        static inline std::vector<LightNode *> chunks;
        static inline std::size_t chunk_pos = 0;
        static void *operator new(std::size_t) {
            if (chunks.empty() || chunk_pos == chunk_size) {
                chunks.push_back(static_cast<LightNode *>(::operator new(chunk_size * sizeof(LightNode))));
                chunk_pos = 0;
            }
            return chunks.back() + (chunk_pos++);
        }
        static void operator delete(void *) noexcept {}
    };

    struct Node {
        Node *l = nullptr, *r = nullptr, *p = nullptr;
        bool rev = false;
        int id = 0;
        Path key, sum, mus;
        LightNode *light = nullptr;   // 自分にぶら下がる軽辺部分木の集約 splay 木の根
        LightNode *belong = nullptr;  // 自分が属する compress splay 木の根であるときの、親の軽辺 splay 木上の対応ノード
    };

    TreeDP dp;
    std::vector<Node> nodes;

    static bool is_root(Node *t) { return !t->p || (t->p->l != t && t->p->r != t); }

    void pull(Node *t) {
        Path base = dp.vertex(t->id);
        Path key = t->light ? dp.add_vertex(base, t->light->sum) : base;
        Path sum = key, mus = key;
        if (t->l) {
            sum = dp.compress(t->l->sum, sum);
            mus = dp.compress(mus, t->l->mus);
        }
        if (t->r) {
            sum = dp.compress(sum, t->r->sum);
            mus = dp.compress(t->r->mus, mus);
        }
        t->key = key;
        t->sum = sum;
        t->mus = mus;
    }

    void toggle(Node *t) {
        std::swap(t->l, t->r);
        std::swap(t->sum, t->mus);
        t->rev = !t->rev;
    }

    void push(Node *t) {
        if (t->rev) {
            if (t->l) toggle(t->l);
            if (t->r) toggle(t->r);
            t->rev = false;
        }
    }

    void propagate_all(Node *t) {
        if (!is_root(t)) propagate_all(t->p);
        push(t);
    }

    void rotate(Node *t) {
        Node *pa = t->p, *gp = pa->p;
        bool is_right_child = (pa->r == t);
        Node *ch = is_right_child ? t->l : t->r;

        if (!is_root(pa)) {
            if (gp->r == pa) gp->r = t;
            else gp->l = t;
        }
        t->p = gp;

        if (is_right_child) {
            pa->r = ch;
            t->l = pa;
        } else {
            pa->l = ch;
            t->r = pa;
        }
        if (ch) ch->p = pa;
        pa->p = t;

        pull(pa);
        pull(t);
    }

    void splay(Node *t) {
        Node *rt = t;
        while (!is_root(rt)) rt = rt->p;
        t->belong = rt->belong;
        if (t != rt) rt->belong = nullptr;

        propagate_all(t);
        while (!is_root(t)) {
            Node *pa = t->p;
            if (!is_root(pa)) {
                Node *gp = pa->p;
                if ((gp->r == pa) == (pa->r == t)) rotate(pa);
                else rotate(t);
            }
            rotate(t);
        }
    }

    Node *expose(Node *t) {
        Node *rp = nullptr;
        for (Node *cur = t; cur; cur = cur->p) {
            splay(cur);
            if (cur->r) {
                cur->light = light_insert(cur->light, dp.add_edge(cur->r->sum));
                cur->r->belong = cur->light;
            }
            cur->r = rp;
            if (cur->r) {
                light_splay(cur->r->belong);
                push(cur->r);
                cur->light = light_erase(cur->r->belong);
            }
            pull(cur);
            rp = cur;
        }
        splay(t);
        return rp;
    }

    void light_pull(LightNode *t) {
        Light s = t->key;
        if (t->l) s = dp.rake(s, t->l->sum);
        if (t->r) s = dp.rake(s, t->r->sum);
        t->sum = s;
    }

    void light_rotate(LightNode *t) {
        LightNode *x = t->p, *y = x->p;
        bool is_right_child = (x->r == t);
        LightNode *ch = is_right_child ? t->l : t->r;

        if (is_right_child) {
            x->r = ch;
            t->l = x;
        } else {
            x->l = ch;
            t->r = x;
        }
        if (ch) ch->p = x;
        x->p = t;

        light_pull(x);
        light_pull(t);
        if ((t->p = y)) {
            if (y->l == x) y->l = t;
            else if (y->r == x) y->r = t;
        }
    }

    void light_splay(LightNode *t) {
        while (t->p) {
            LightNode *q = t->p;
            if (q->p) {
                LightNode *r = q->p;
                if ((r->l == q) == (q->l == t)) light_rotate(q);
                else light_rotate(t);
            }
            light_rotate(t);
        }
    }

    static LightNode *light_rightmost(LightNode *t) {
        while (t->r) t = t->r;
        return t;
    }

    LightNode *light_insert(LightNode *root, const Light &v) {
        LightNode *z = new LightNode(v);
        if (!root) return z;
        LightNode *cur = light_rightmost(root);
        light_splay(cur);
        z->p = cur;
        cur->r = z;
        light_pull(cur);
        light_splay(z);
        return z;
    }

    LightNode *light_erase(LightNode *t) {
        light_splay(t);
        LightNode *x = t->l, *y = t->r;
        if (!x) {
            if (y) y->p = nullptr;
            return y;
        }
        if (!y) {
            x->p = nullptr;
            return x;
        }
        x->p = nullptr;
        LightNode *w = light_rightmost(x);
        light_splay(w);
        w->r = y;
        y->p = w;
        light_pull(w);
        return w;
    }
};
