#include <algorithm>
#include <cstdint>
#include <vector>

/**
 * @brief kd-tree
 *
 * @see https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html
 */
struct kdtree {
  private:
    struct _point {
        int id;
        int x, y;

        constexpr _point() : id(), x(), y() {}
        constexpr _point(int id, int x, int y) : id(id), x(x), y(y) {}
    };
    struct _node {
        int left, right;
        _point p;

        constexpr _node() : left(), right(), p() {}
        constexpr _node(int left, int right, _point p) : left(left), right(right), p(p) {}
    };

  public:
    kdtree() : points(), nodes() {}

    void add(int x, int y) {
        int id = this->points.size();
        this->points.emplace_back(id, x, y);
    }

    void build() { this->build(0, this->points.size(), 0); }

    std::int64_t find(int x, int y) { return this->find(0, x, y, 0, -1); }

    // [sx, tx) * [sy, ty)
    std::vector<int> find(int sx, int tx, int sy, int ty) {
        return this->find(0, sx, tx, sy, ty, 0);
    }

  private:
    std::vector<_point> points;
    std::vector<_node> nodes;

    int build(int l, int r, int depth) {
        if (l == r) { return -1; }
        if (r - l == 1) {
            int res = this->nodes.size();
            this->nodes.emplace_back(-1, -1, this->points[l]);
            return res;
        }
        int mid = (l + r) >> 1;
        if (depth & 1) {
            std::sort(this->points.begin() + l, this->points.begin() + r,
                      [](const _point &a, const _point &b) { return a.x < b.x; });
        } else {
            std::sort(this->points.begin() + l, this->points.begin() + r,
                      [](const _point &a, const _point &b) { return a.y < b.y; });
        }
        int res = this->nodes.size();
        this->nodes.emplace_back();
        int left = this->build(l, mid, depth + 1);
        int right = this->build(mid + 1, r, depth + 1);
        this->nodes[res] = _node(left, right, this->points[mid]);
        return res;
    }

    std::int64_t find(int idx, int x, int y, int depth, std::int64_t r) {
        if (idx == -1) return r;
        _point &p = this->nodes[idx].p;
        std::int64_t d = std::int64_t(x - p.x) * (x - p.x) + std::int64_t(y - p.y) * (y - p.y);
        if (r == -1 || d < r) r = d;

        if (depth & 1) {
            if (this->nodes[idx].left != -1 && x - r <= p.x) {
                r = this->find(this->nodes[idx].left, x, y, depth + 1, r);
            }
            if (this->nodes[idx].right != -1 && p.x <= x + r) {
                r = this->find(this->nodes[idx].right, x, y, depth + 1, r);
            }
        } else {
            if (this->nodes[idx].left != -1 && y - r <= p.y) {
                r = this->find(this->nodes[idx].left, x, y, depth + 1, r);
            }
            if (this->nodes[idx].right != -1 && p.y <= y + r) {
                r = this->find(this->nodes[idx].right, x, y, depth + 1, r);
            }
        }
        return r;
    }

    std::vector<int> find(int idx, int sx, int tx, int sy, int ty, int depth) {
        std::vector<int> res;
        _point &p = this->nodes[idx].p;
        if (sx <= p.x && p.x < tx && sy <= p.y && p.y < ty) { res.emplace_back(p.id); }

        if (depth & 1) {
            if (this->nodes[idx].left != -1 && sx <= p.x) {
                auto v = this->find(this->nodes[idx].left, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
            if (this->nodes[idx].right != -1 && p.x < tx) {
                auto v = this->find(this->nodes[idx].right, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
        } else {
            if (this->nodes[idx].left != -1 && sy <= p.y) {
                auto v = this->find(this->nodes[idx].left, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
            if (this->nodes[idx].right != -1 && p.y < ty) {
                auto v = this->find(this->nodes[idx].right, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
        }
        return res;
    }
};
