---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/range_search.test.cpp
    title: test/aoj/dsl/range_search.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: kd-tree
    links:
    - https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html
  bundledCode: "#line 1 \"lib/geometry/kdtree.hpp\"\n#include <algorithm>\r\n#include\
    \ <cstdint>\r\n#include <vector>\r\n\r\n/**\r\n * @brief kd-tree\r\n *\r\n * @see\
    \ https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html\r\n */\r\
    \nstruct kdtree {\r\n  private:\r\n    struct _point {\r\n        int id;\r\n\
    \        int x, y;\r\n\r\n        constexpr _point() : id(), x(), y() {}\r\n \
    \       constexpr _point(int id, int x, int y) : id(id), x(x), y(y) {}\r\n   \
    \ };\r\n    struct _node {\r\n        int left, right;\r\n        _point p;\r\n\
    \r\n        constexpr _node() : left(), right(), p() {}\r\n        constexpr _node(int\
    \ left, int right, _point p) : left(left), right(right), p(p) {}\r\n    };\r\n\
    \r\n  public:\r\n    kdtree() : points(), nodes() {}\r\n\r\n    void add(int x,\
    \ int y) {\r\n        int id = this->points.size();\r\n        this->points.emplace_back(id,\
    \ x, y);\r\n    }\r\n\r\n    void build() { this->build(0, this->points.size(),\
    \ 0); }\r\n\r\n    std::int64_t find(int x, int y) { return this->find(0, x, y,\
    \ 0, -1); }\r\n\r\n    // [sx, tx) * [sy, ty)\r\n    std::vector<int> find(int\
    \ sx, int tx, int sy, int ty) {\r\n        return this->find(0, sx, tx, sy, ty,\
    \ 0);\r\n    }\r\n\r\n  private:\r\n    std::vector<_point> points;\r\n    std::vector<_node>\
    \ nodes;\r\n\r\n    int build(int l, int r, int depth) {\r\n        if (l == r)\
    \ { return -1; }\r\n        if (r - l == 1) {\r\n            int res = this->nodes.size();\r\
    \n            this->nodes.emplace_back(-1, -1, this->points[l]);\r\n         \
    \   return res;\r\n        }\r\n        int mid = (l + r) >> 1;\r\n        if\
    \ (depth & 1) {\r\n            std::sort(this->points.begin() + l, this->points.begin()\
    \ + r,\r\n                      [](const _point &a, const _point &b) { return\
    \ a.x < b.x; });\r\n        } else {\r\n            std::sort(this->points.begin()\
    \ + l, this->points.begin() + r,\r\n                      [](const _point &a,\
    \ const _point &b) { return a.y < b.y; });\r\n        }\r\n        int res = this->nodes.size();\r\
    \n        this->nodes.emplace_back();\r\n        int left = this->build(l, mid,\
    \ depth + 1);\r\n        int right = this->build(mid + 1, r, depth + 1);\r\n \
    \       this->nodes[res] = _node(left, right, this->points[mid]);\r\n        return\
    \ res;\r\n    }\r\n\r\n    std::int64_t find(int idx, int x, int y, int depth,\
    \ std::int64_t r) {\r\n        if (idx == -1) return r;\r\n        _point &p =\
    \ this->nodes[idx].p;\r\n        std::int64_t d = std::int64_t(x - p.x) * (x -\
    \ p.x) + std::int64_t(y - p.y) * (y - p.y);\r\n        if (r == -1 || d < r) r\
    \ = d;\r\n\r\n        if (depth & 1) {\r\n            if (this->nodes[idx].left\
    \ != -1 && x - r <= p.x) {\r\n                r = this->find(this->nodes[idx].left,\
    \ x, y, depth + 1, r);\r\n            }\r\n            if (this->nodes[idx].right\
    \ != -1 && p.x <= x + r) {\r\n                r = this->find(this->nodes[idx].right,\
    \ x, y, depth + 1, r);\r\n            }\r\n        } else {\r\n            if\
    \ (this->nodes[idx].left != -1 && y - r <= p.y) {\r\n                r = this->find(this->nodes[idx].left,\
    \ x, y, depth + 1, r);\r\n            }\r\n            if (this->nodes[idx].right\
    \ != -1 && p.y <= y + r) {\r\n                r = this->find(this->nodes[idx].right,\
    \ x, y, depth + 1, r);\r\n            }\r\n        }\r\n        return r;\r\n\
    \    }\r\n\r\n    std::vector<int> find(int idx, int sx, int tx, int sy, int ty,\
    \ int depth) {\r\n        std::vector<int> res;\r\n        _point &p = this->nodes[idx].p;\r\
    \n        if (sx <= p.x && p.x < tx && sy <= p.y && p.y < ty) { res.emplace_back(p.id);\
    \ }\r\n\r\n        if (depth & 1) {\r\n            if (this->nodes[idx].left !=\
    \ -1 && sx <= p.x) {\r\n                auto v = this->find(this->nodes[idx].left,\
    \ sx, tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n            if (this->nodes[idx].right != -1 &&\
    \ p.x < tx) {\r\n                auto v = this->find(this->nodes[idx].right, sx,\
    \ tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n        } else {\r\n            if (this->nodes[idx].left\
    \ != -1 && sy <= p.y) {\r\n                auto v = this->find(this->nodes[idx].left,\
    \ sx, tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n            if (this->nodes[idx].right != -1 &&\
    \ p.y < ty) {\r\n                auto v = this->find(this->nodes[idx].right, sx,\
    \ tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n        }\r\n        return res;\r\n    }\r\n\
    };\r\n"
  code: "#include <algorithm>\r\n#include <cstdint>\r\n#include <vector>\r\n\r\n/**\r\
    \n * @brief kd-tree\r\n *\r\n * @see https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html\r\
    \n */\r\nstruct kdtree {\r\n  private:\r\n    struct _point {\r\n        int id;\r\
    \n        int x, y;\r\n\r\n        constexpr _point() : id(), x(), y() {}\r\n\
    \        constexpr _point(int id, int x, int y) : id(id), x(x), y(y) {}\r\n  \
    \  };\r\n    struct _node {\r\n        int left, right;\r\n        _point p;\r\
    \n\r\n        constexpr _node() : left(), right(), p() {}\r\n        constexpr\
    \ _node(int left, int right, _point p) : left(left), right(right), p(p) {}\r\n\
    \    };\r\n\r\n  public:\r\n    kdtree() : points(), nodes() {}\r\n\r\n    void\
    \ add(int x, int y) {\r\n        int id = this->points.size();\r\n        this->points.emplace_back(id,\
    \ x, y);\r\n    }\r\n\r\n    void build() { this->build(0, this->points.size(),\
    \ 0); }\r\n\r\n    std::int64_t find(int x, int y) { return this->find(0, x, y,\
    \ 0, -1); }\r\n\r\n    // [sx, tx) * [sy, ty)\r\n    std::vector<int> find(int\
    \ sx, int tx, int sy, int ty) {\r\n        return this->find(0, sx, tx, sy, ty,\
    \ 0);\r\n    }\r\n\r\n  private:\r\n    std::vector<_point> points;\r\n    std::vector<_node>\
    \ nodes;\r\n\r\n    int build(int l, int r, int depth) {\r\n        if (l == r)\
    \ { return -1; }\r\n        if (r - l == 1) {\r\n            int res = this->nodes.size();\r\
    \n            this->nodes.emplace_back(-1, -1, this->points[l]);\r\n         \
    \   return res;\r\n        }\r\n        int mid = (l + r) >> 1;\r\n        if\
    \ (depth & 1) {\r\n            std::sort(this->points.begin() + l, this->points.begin()\
    \ + r,\r\n                      [](const _point &a, const _point &b) { return\
    \ a.x < b.x; });\r\n        } else {\r\n            std::sort(this->points.begin()\
    \ + l, this->points.begin() + r,\r\n                      [](const _point &a,\
    \ const _point &b) { return a.y < b.y; });\r\n        }\r\n        int res = this->nodes.size();\r\
    \n        this->nodes.emplace_back();\r\n        int left = this->build(l, mid,\
    \ depth + 1);\r\n        int right = this->build(mid + 1, r, depth + 1);\r\n \
    \       this->nodes[res] = _node(left, right, this->points[mid]);\r\n        return\
    \ res;\r\n    }\r\n\r\n    std::int64_t find(int idx, int x, int y, int depth,\
    \ std::int64_t r) {\r\n        if (idx == -1) return r;\r\n        _point &p =\
    \ this->nodes[idx].p;\r\n        std::int64_t d = std::int64_t(x - p.x) * (x -\
    \ p.x) + std::int64_t(y - p.y) * (y - p.y);\r\n        if (r == -1 || d < r) r\
    \ = d;\r\n\r\n        if (depth & 1) {\r\n            if (this->nodes[idx].left\
    \ != -1 && x - r <= p.x) {\r\n                r = this->find(this->nodes[idx].left,\
    \ x, y, depth + 1, r);\r\n            }\r\n            if (this->nodes[idx].right\
    \ != -1 && p.x <= x + r) {\r\n                r = this->find(this->nodes[idx].right,\
    \ x, y, depth + 1, r);\r\n            }\r\n        } else {\r\n            if\
    \ (this->nodes[idx].left != -1 && y - r <= p.y) {\r\n                r = this->find(this->nodes[idx].left,\
    \ x, y, depth + 1, r);\r\n            }\r\n            if (this->nodes[idx].right\
    \ != -1 && p.y <= y + r) {\r\n                r = this->find(this->nodes[idx].right,\
    \ x, y, depth + 1, r);\r\n            }\r\n        }\r\n        return r;\r\n\
    \    }\r\n\r\n    std::vector<int> find(int idx, int sx, int tx, int sy, int ty,\
    \ int depth) {\r\n        std::vector<int> res;\r\n        _point &p = this->nodes[idx].p;\r\
    \n        if (sx <= p.x && p.x < tx && sy <= p.y && p.y < ty) { res.emplace_back(p.id);\
    \ }\r\n\r\n        if (depth & 1) {\r\n            if (this->nodes[idx].left !=\
    \ -1 && sx <= p.x) {\r\n                auto v = this->find(this->nodes[idx].left,\
    \ sx, tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n            if (this->nodes[idx].right != -1 &&\
    \ p.x < tx) {\r\n                auto v = this->find(this->nodes[idx].right, sx,\
    \ tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n        } else {\r\n            if (this->nodes[idx].left\
    \ != -1 && sy <= p.y) {\r\n                auto v = this->find(this->nodes[idx].left,\
    \ sx, tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n            if (this->nodes[idx].right != -1 &&\
    \ p.y < ty) {\r\n                auto v = this->find(this->nodes[idx].right, sx,\
    \ tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n        }\r\n        return res;\r\n    }\r\n\
    };\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/geometry/kdtree.hpp
  requiredBy: []
  timestamp: '2024-04-28 13:30:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/range_search.test.cpp
documentation_of: lib/geometry/kdtree.hpp
layout: document
redirect_from:
- /library/lib/geometry/kdtree.hpp
- /library/lib/geometry/kdtree.hpp.html
title: kd-tree
---
