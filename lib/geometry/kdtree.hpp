#include "template/template.hpp"

/*
 * reference :
 * https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html
 * verify :
 * https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C 21/03/29
 * https://atcoder.jp/contests/arc010/tasks/arc010_4 21/03/30
 */
struct kdtree {
    struct Point {
        int id;
        int x, y;
    };
    struct Node {
        int left, right;
        Point p;
    };

    vector<Point> points;
    vector<Node> nodes;

    kdtree() : points(), nodes() {}

    void add(int x, int y) {
        int id = points.size();
        points.emplace_back(Point{id, x, y});
    }

    int make(int l, int r, int depth) {
        if (l == r) {
            return -1;
        }
        if (r - l == 1) {
            int res = nodes.size();
            nodes.emplace_back(Node{-1, -1, points[l]});
            return res;
        }
        int mid = (l + r) >> 1;
        if (depth & 1) {
            sort(points.begin() + l, points.begin() + r,
                 [](const Point &a, const Point &b) { return a.x < b.x; });
        } else {
            sort(points.begin() + l, points.begin() + r,
                 [](const Point &a, const Point &b) { return a.y < b.y; });
        }
        int res = nodes.size();
        nodes.emplace_back(Node{});
        int left = make(l, mid, depth + 1);
        int right = make(mid + 1, r, depth + 1);
        nodes[res] = Node{left, right, points[mid]};
        return res;
    }
    void build() { make(0, points.size(), 0); }

    int64_t find(int idx, int x, int y, int depth, int64_t r) {
        if (idx == -1) return r;
        Point &p = nodes[idx].p;
        int64_t d = int64_t(x - p.x) * (x - p.x) + int64_t(y - p.y) * (y - p.y);
        if (r == -1 || d < r) r = d;

        if (depth & 1) {
            if (nodes[idx].left != -1 && x - r <= p.x) {
                r = find(nodes[idx].left, x, y, depth + 1, r);
            }
            if (nodes[idx].right != -1 && p.x <= x + r) {
                r = find(nodes[idx].right, x, y, depth + 1, r);
            }
        } else {
            if (nodes[idx].left != -1 && y - r <= p.y) {
                r = find(nodes[idx].left, x, y, depth + 1, r);
            }
            if (nodes[idx].right != -1 && p.y <= y + r) {
                r = find(nodes[idx].right, x, y, depth + 1, r);
            }
        }
        return r;
    }
    int64_t find(int x, int y) { return find(0, x, y, 0, -1); }

    // [sx, tx) * [sy, ty)
    vector<int> find(int idx, int sx, int tx, int sy, int ty, int depth) {
        vector<int> res;
        Point &p = nodes[idx].p;
        if (sx <= p.x && p.x < tx && sy <= p.y && p.y < ty) {
            res.emplace_back(p.id);
        }

        if (depth & 1) {
            if (nodes[idx].left != -1 && sx <= p.x) {
                auto v = find(nodes[idx].left, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
            if (nodes[idx].right != -1 && p.x < tx) {
                auto v = find(nodes[idx].right, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
        } else {
            if (nodes[idx].left != -1 && sy <= p.y) {
                auto v = find(nodes[idx].left, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
            if (nodes[idx].right != -1 && p.y < ty) {
                auto v = find(nodes[idx].right, sx, tx, sy, ty, depth + 1);
                res.insert(res.end(), v.begin(), v.end());
            }
        }
        return res;
    }
    vector<int> find(int sx, int tx, int sy, int ty) {
        return find(0, sx, tx, sy, ty, 0);
    }
};
