---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/convex_hull.test.cpp
    title: test/aoj/cgl/convex_hull.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u70B9"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u70B9\r\n *\r\
    \n * @tparam T \u5EA7\u6A19\u306E\u578B\r\n */\r\ntemplate <class T>\r\nstruct\
    \ Point {\r\n    T x, y;\r\n\r\n    constexpr Point() : x(), y() {}\r\n    constexpr\
    \ Point(T _x, T _y) : x(_x), y(_y) {}\r\n\r\n    constexpr Point &operator-=(const\
    \ Point &rhs) {\r\n        this->x -= rhs.x, this->y -= rhs.y;\r\n        return\
    \ *this;\r\n    }\r\n\r\n    friend std::istream &operator>>(std::istream &is,\
    \ Point &rhs) {\r\n        T x, y;\r\n        is >> x >> y;\r\n        rhs = Point(x,\
    \ y);\r\n        return (is);\r\n    }\r\n};\r\n\r\n/**\r\n * @brief \u51F8\u6CD5\
    \r\n *\r\n * @tparam T \u5EA7\u6A19\u306E\u578B\r\n * @param points \u70B9\u96C6\
    \u5408\r\n * @return std::vector<Point<T>>\r\n */\r\ntemplate <class T>\r\nstd::vector<Point<T>>\
    \ convex_hull(std::vector<Point<T>> points) {\r\n    int n = points.size(), k\
    \ = 0;\r\n    std::sort(points.begin(), points.end(), [](const Point<T> &a, const\
    \ Point<T> &b) {\r\n        return a.x != b.x ? a.x < b.x : a.y < b.y;\r\n   \
    \ });\r\n    std::vector<Point<T>> res(n << 1);\r\n    auto cross = [](Point<T>\
    \ a, Point<T> b, const Point<T> &c) {\r\n        a -= c, b -= c;\r\n        return\
    \ a.x * b.y - a.y * b.x;\r\n    };\r\n    for (int i = 0; i < n; ++i) {\r\n  \
    \      while (k > 1 && cross(points[i], res[k - 2], res[k - 1]) < 0) --k;\r\n\
    \        res[k++] = points[i];\r\n    }\r\n    for (int i = n - 2, t = k; i >=\
    \ 0; --i) {\r\n        while (k > t && cross(points[i], res[k - 2], res[k - 1])\
    \ < 0) --k;\r\n        res[k++] = points[i];\r\n    }\r\n    res.resize(k - 1);\r\
    \n    return res;\r\n}\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/geometry/convex_hull.hpp
  requiredBy: []
  timestamp: '2023-09-26 21:06:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/cgl/convex_hull.test.cpp
documentation_of: lib/geometry/convex_hull.hpp
layout: document
redirect_from:
- /library/lib/geometry/convex_hull.hpp
- /library/lib/geometry/convex_hull.hpp.html
title: "\u70B9"
---
