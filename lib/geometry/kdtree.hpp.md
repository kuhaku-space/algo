---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/arc010/tasks/arc010_4
    - https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C
    - https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/*\r\n * reference :\r\n * https://tjkendev.github.io/procon-library/cpp/range_query/kd-tree.html\r\
    \n * verify :\r\n * https://onlinejudge.u-aizu.ac.jp/problems/DSL_2_C 21/03/29\r\
    \n * https://atcoder.jp/contests/arc010/tasks/arc010_4 21/03/30\r\n */\r\nstruct\
    \ kdtree {\r\n    struct Point {\r\n        int id;\r\n        int x, y;\r\n \
    \   };\r\n    struct Node {\r\n        int left, right;\r\n        Point p;\r\n\
    \    };\r\n\r\n    vector<Point> points;\r\n    vector<Node> nodes;\r\n\r\n  \
    \  kdtree() : points(), nodes() {}\r\n\r\n    void add(int x, int y) {\r\n   \
    \     int id = points.size();\r\n        points.emplace_back(Point{id, x, y});\r\
    \n    }\r\n\r\n    int make(int l, int r, int depth) {\r\n        if (l == r)\
    \ {\r\n            return -1;\r\n        }\r\n        if (r - l == 1) {\r\n  \
    \          int res = nodes.size();\r\n            nodes.emplace_back(Node{-1,\
    \ -1, points[l]});\r\n            return res;\r\n        }\r\n        int mid\
    \ = (l + r) >> 1;\r\n        if (depth & 1) {\r\n            sort(points.begin()\
    \ + l, points.begin() + r,\r\n                 [](const Point &a, const Point\
    \ &b) { return a.x < b.x; });\r\n        } else {\r\n            sort(points.begin()\
    \ + l, points.begin() + r,\r\n                 [](const Point &a, const Point\
    \ &b) { return a.y < b.y; });\r\n        }\r\n        int res = nodes.size();\r\
    \n        nodes.emplace_back(Node{});\r\n        int left = make(l, mid, depth\
    \ + 1);\r\n        int right = make(mid + 1, r, depth + 1);\r\n        nodes[res]\
    \ = Node{left, right, points[mid]};\r\n        return res;\r\n    }\r\n    void\
    \ build() { make(0, points.size(), 0); }\r\n\r\n    int64_t find(int idx, int\
    \ x, int y, int depth, int64_t r) {\r\n        if (idx == -1) return r;\r\n  \
    \      Point &p = nodes[idx].p;\r\n        int64_t d = int64_t(x - p.x) * (x -\
    \ p.x) + int64_t(y - p.y) * (y - p.y);\r\n        if (r == -1 || d < r) r = d;\r\
    \n\r\n        if (depth & 1) {\r\n            if (nodes[idx].left != -1 && x -\
    \ r <= p.x) {\r\n                r = find(nodes[idx].left, x, y, depth + 1, r);\r\
    \n            }\r\n            if (nodes[idx].right != -1 && p.x <= x + r) {\r\
    \n                r = find(nodes[idx].right, x, y, depth + 1, r);\r\n        \
    \    }\r\n        } else {\r\n            if (nodes[idx].left != -1 && y - r <=\
    \ p.y) {\r\n                r = find(nodes[idx].left, x, y, depth + 1, r);\r\n\
    \            }\r\n            if (nodes[idx].right != -1 && p.y <= y + r) {\r\n\
    \                r = find(nodes[idx].right, x, y, depth + 1, r);\r\n         \
    \   }\r\n        }\r\n        return r;\r\n    }\r\n    int64_t find(int x, int\
    \ y) { return find(0, x, y, 0, -1); }\r\n\r\n    // [sx, tx) * [sy, ty)\r\n  \
    \  vector<int> find(int idx, int sx, int tx, int sy, int ty, int depth) {\r\n\
    \        vector<int> res;\r\n        Point &p = nodes[idx].p;\r\n        if (sx\
    \ <= p.x && p.x < tx && sy <= p.y && p.y < ty) {\r\n            res.emplace_back(p.id);\r\
    \n        }\r\n\r\n        if (depth & 1) {\r\n            if (nodes[idx].left\
    \ != -1 && sx <= p.x) {\r\n                auto v = find(nodes[idx].left, sx,\
    \ tx, sy, ty, depth + 1);\r\n                res.insert(res.end(), v.begin(),\
    \ v.end());\r\n            }\r\n            if (nodes[idx].right != -1 && p.x\
    \ < tx) {\r\n                auto v = find(nodes[idx].right, sx, tx, sy, ty, depth\
    \ + 1);\r\n                res.insert(res.end(), v.begin(), v.end());\r\n    \
    \        }\r\n        } else {\r\n            if (nodes[idx].left != -1 && sy\
    \ <= p.y) {\r\n                auto v = find(nodes[idx].left, sx, tx, sy, ty,\
    \ depth + 1);\r\n                res.insert(res.end(), v.begin(), v.end());\r\n\
    \            }\r\n            if (nodes[idx].right != -1 && p.y < ty) {\r\n  \
    \              auto v = find(nodes[idx].right, sx, tx, sy, ty, depth + 1);\r\n\
    \                res.insert(res.end(), v.begin(), v.end());\r\n            }\r\
    \n        }\r\n        return res;\r\n    }\r\n    vector<int> find(int sx, int\
    \ tx, int sy, int ty) {\r\n        return find(0, sx, tx, sy, ty, 0);\r\n    }\r\
    \n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/kdtree.hpp
  requiredBy: []
  timestamp: '2021-09-18 19:45:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/geometry/kdtree.hpp
layout: document
redirect_from:
- /library/lib/geometry/kdtree.hpp
- /library/lib/geometry/kdtree.hpp.html
title: lib/geometry/kdtree.hpp
---
