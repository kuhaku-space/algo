---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj/all_pairs_shortest_path.test.cpp
    title: test/aoj/all_pairs_shortest_path.test.cpp
  - icon: ':x:'
    path: test/aoj/dp/bell.test.cpp
    title: test/aoj/dp/bell.test.cpp
  - icon: ':x:'
    path: test/aoj/dp/stirling.test.cpp
    title: test/aoj/dp/stirling.test.cpp
  - icon: ':x:'
    path: test/aoj/geometry/counter-clockwise.test.cpp
    title: test/aoj/geometry/counter-clockwise.test.cpp
  - icon: ':x:'
    path: test/aoj/geometry/cross_point.test.cpp
    title: test/aoj/geometry/cross_point.test.cpp
  - icon: ':x:'
    path: test/aoj/geometry/intersection.test.cpp
    title: test/aoj/geometry/intersection.test.cpp
  - icon: ':x:'
    path: test/aoj/geometry/parallel_orthogonal.test.cpp
    title: test/aoj/geometry/parallel_orthogonal.test.cpp
  - icon: ':x:'
    path: test/aoj/geometry/projection.test.cpp
    title: test/aoj/geometry/projection.test.cpp
  - icon: ':x:'
    path: test/aoj/geometry/reflection.test.cpp
    title: test/aoj/geometry/reflection.test.cpp
  - icon: ':x:'
    path: test/aoj/longest_increasing_subsequense.test.cpp
    title: test/aoj/longest_increasing_subsequense.test.cpp
  - icon: ':x:'
    path: test/aoj/power.test.cpp
    title: test/aoj/power.test.cpp
  - icon: ':x:'
    path: test/aoj/prime_factorize.test.cpp
    title: test/aoj/prime_factorize.test.cpp
  - icon: ':x:'
    path: test/aoj/prime_numbers.test.cpp
    title: test/aoj/prime_numbers.test.cpp
  - icon: ':x:'
    path: test/aoj/the_number_of_inversions.test.cpp
    title: test/aoj/the_number_of_inversions.test.cpp
  - icon: ':x:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  - icon: ':x:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo/data_structure/set_xor-min.test.cpp
    title: test/yosupo/data_structure/set_xor-min.test.cpp
  - icon: ':x:'
    path: test/yosupo/data_structure/static_range_sum.test.cpp
    title: test/yosupo/data_structure/static_range_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  - icon: ':x:'
    path: test/yosupo/data_structure/unionfind.test.cpp
    title: test/yosupo/data_structure/unionfind.test.cpp
  - icon: ':x:'
    path: test/yosupo/graph/shortest_path.test.cpp
    title: test/yosupo/graph/shortest_path.test.cpp
  - icon: ':x:'
    path: test/yosupo/sample/many_a+b.test.cpp
    title: test/yosupo/sample/many_a+b.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.0/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#pragma GCC target(\"avx\")\n#pragma GCC optimize(\"O3\")\n\
    #pragma GCC optimize(\"unroll-loops\")\n#include \"template/template.hpp\"\nusing\
    \ ll = int64_t;\nusing ld = long double;\n#define FOR(i, m, n) for(int i = (m);\
    \ i < (n); ++i)\n#define FORR(i, m, n) for(int i = (m)-1; i >= (n); --i)\n#define\
    \ FORL(i, m, n) for(ll i = (m); i < (n); ++i)\n#define rep(i, n) FOR(i, 0, n)\n\
    #define repn(i, n) FOR(i, 1, n+1)\n#define repr(i, n) FORR(i, n, 0)\n#define repnr(i,\
    \ n) FORR(i, n+1, 1)\n#define all(s) (s).begin(), (s).end()\ntemplate<class T,\
    \ class U>\nistream &operator>>(istream &is, pair<T, U> &p) { is >> p.first >>\
    \ p.second; return is }\ntemplate <class T>\nistream &operator>>(istream &is,\
    \ vector<T> &v) { for (T &i : v) is>>i; return is; }\ntemplate <class T>\nostream\
    \ &operator<<(ostream &os, const vector<T> &v) {\n    for (auto it=v.begin();\
    \ it!=v.end(); ++it) { os<<(it==v.begin()?\"\":\" \")<<*it; } return os;\n}\n\
    template <class Head, class... Tail>\nvoid co(Head&& head, Tail&&... tail) {\n\
    \    if constexpr(sizeof...(tail)==0) cout<<head<<'\\n'; else cout<<head<<' ',co(forward<Tail>(tail)...);\n\
    }\ntemplate <class Head, class... Tail>\nvoid ce(Head&& head, Tail&&... tail)\
    \ {\n    if constexpr(sizeof...(tail)==0) cerr<<head<<'\\n'; else cerr<<head<<'\
    \ ',ce(forward<Tail>(tail)...);\n}\ntemplate<typename T, typename... Args>\nauto\
    \ make_vector(T x, int arg, Args ...args) {\n    if constexpr(sizeof...(args)==0)\
    \ return vector<T>(arg, x); else return vector(arg,make_vector<T>(x, args...));\n\
    }\nvoid sonic() { ios::sync_with_stdio(false); cin.tie(nullptr); }\nvoid setp(const\
    \ int n) { cout << fixed << setprecision(n); }"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/template/atcoder.hpp
  requiredBy: []
  timestamp: '2021-12-04 19:53:58+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo/graph/shortest_path.test.cpp
  - test/yosupo/data_structure/set_xor-min.test.cpp
  - test/yosupo/data_structure/static_rmq.test.cpp
  - test/yosupo/data_structure/static_range_sum.test.cpp
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
  - test/yosupo/data_structure/unionfind.test.cpp
  - test/yosupo/sample/many_a+b.test.cpp
  - test/yosupo/convolution/convolution_mod.test.cpp
  - test/aoj/the_number_of_inversions.test.cpp
  - test/aoj/geometry/counter-clockwise.test.cpp
  - test/aoj/geometry/parallel_orthogonal.test.cpp
  - test/aoj/geometry/reflection.test.cpp
  - test/aoj/geometry/projection.test.cpp
  - test/aoj/geometry/intersection.test.cpp
  - test/aoj/geometry/cross_point.test.cpp
  - test/aoj/dp/stirling.test.cpp
  - test/aoj/dp/bell.test.cpp
  - test/aoj/all_pairs_shortest_path.test.cpp
  - test/aoj/longest_increasing_subsequense.test.cpp
  - test/aoj/power.test.cpp
  - test/aoj/prime_numbers.test.cpp
  - test/aoj/prime_factorize.test.cpp
documentation_of: lib/template/atcoder.hpp
layout: document
redirect_from:
- /library/lib/template/atcoder.hpp
- /library/lib/template/atcoder.hpp.html
title: lib/template/atcoder.hpp
---
