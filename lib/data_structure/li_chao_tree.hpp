#include "template/template.hpp"

struct li_chao_tree {
  private:
    struct _line {
        std::int64_t a, b;

        constexpr _line(std::int64_t _a, std::int64_t _b) : a(_a), b(_b) {}
        constexpr std::int64_t operator()(std::int64_t x) const { return a * x + b; }
    };

    const _line inf_line = {0, inf};

    struct _node {
        using pointer = _node *;
        pointer left, right;
        _line line;

        constexpr _node(_line line) : left(nullptr), right(nullptr), line(line) {}
    };

  public:
    using line_type = _line;
    using node_ptr = typename _node::pointer;

    static constexpr std::int64_t inf = std::numeric_limits<std::int64_t>::max();

    constexpr li_chao_tree(std::int64_t _xr) : root(nullptr), xl(0), xr(_xr) {}
    constexpr li_chao_tree(std::int64_t _xl, std::int64_t _xr) : root(nullptr), xl(_xl), xr(_xr) {}

    /**
     * @brief Add line ($ax+b$)
     *
     * @param a
     * @param b
     */
    void add_line(std::int64_t a, std::int64_t b) {
        _line line = _line{a, b};
        this->root = this->add_line(this->root, line, this->xl, this->xr);
    }

    /**
     * @brief Add segment ($ax+b$)
     *
     * @param a
     * @param b
     * @param l
     * @param r
     */
    void add_segment(std::int64_t a, std::int64_t b, std::int64_t l, std::int64_t r) {
        assert(this->xl <= l && l < r && r <= this->xr);
        _line line = _line{a, b};
        this->root = this->add_segment(l, r, this->root, line, this->xl, this->xr);
    }

    std::int64_t query(std::int64_t x) {
        assert(this->xl <= x && x < this->xr);
        return this->query(x, this->xl, this->xr);
    }

  private:
    node_ptr root;
    std::int64_t xl, xr;

    node_ptr add_line(node_ptr node, _line line, std::int64_t l, std::int64_t r) {
        if (node == nullptr) return new _node(line);
        if (l + 1 == r) {
            if (line(l) < node->line(l)) node->line = line;
            return node;
        }
        std::int64_t m = (l + r) >> 1;
        bool left = (line(l) < node->line(l));
        bool right = (line(r) < node->line(r));
        if (left && right) {
            node->line = line;
            return node;
        }
        if (!left && !right) return node;
        bool mid = (line(m) < node->line(m));
        if (mid) swap(node->line, line);
        if (left != mid) node->left = this->add_line(node->left, line, l, m);
        else node->right = this->add_line(node->right, line, m, r);
        return node;
    }

    node_ptr add_segment(std::int64_t a, std::int64_t b, node_ptr node, _line line, std::int64_t l,
                         std::int64_t r) {
        if (r <= a || b <= l) return node;
        if (a <= l && r <= b) return this->add_line(node, line, l, r);
        if (node == nullptr) node = new _node(inf_line);
        std::int64_t m = (l + r) >> 1;
        node->left = this->add_segment(a, b, node->left, line, l, m);
        node->right = this->add_segment(a, b, node->right, line, m, r);
        return node;
    }

    std::int64_t query(std::int64_t k, std::int64_t l, std::int64_t r) {
        node_ptr node = this->root;
        std::int64_t s = inf;
        while (node != nullptr) {
            std::int64_t m = (l + r) >> 1;
            chmin(s, node->line(k));
            if (k < m) r = m, node = node->left;
            else l = m, node = node->right;
        }
        return s;
    }
};
