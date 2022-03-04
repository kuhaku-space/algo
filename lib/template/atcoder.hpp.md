---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/inversion_number.test.cpp
    title: test/aoj/alds1/inversion_number.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/prime_numbers.test.cpp
    title: test/aoj/alds1/prime_numbers.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/counter-clockwise.test.cpp
    title: test/aoj/cgl/counter-clockwise.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/cross_point.test.cpp
    title: test/aoj/cgl/cross_point.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/intersection.test.cpp
    title: test/aoj/cgl/intersection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/parallel_orthogonal.test.cpp
    title: test/aoj/cgl/parallel_orthogonal.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/projection.test.cpp
    title: test/aoj/cgl/projection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/cgl/reflection.test.cpp
    title: test/aoj/cgl/reflection.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/bell.test.cpp
    title: test/aoj/dpl/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/longest_increasing_subsequense.test.cpp
    title: test/aoj/dpl/longest_increasing_subsequense.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/stirling.test.cpp
    title: test/aoj/dpl/stirling.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/rmq.test.cpp
    title: test/aoj/dsl/rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/ruq.test.cpp
    title: test/aoj/dsl/ruq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/bellman_ford.test.cpp
    title: test/aoj/grl/bellman_ford.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra.test.cpp
    title: test/aoj/grl/dijkstra.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/hld.test.cpp
    title: test/aoj/grl/hld.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/warshall_floyd.test.cpp
    title: test/aoj/grl/warshall_floyd.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/power.test.cpp
    title: test/aoj/ntl/power.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/prime_factorize.test.cpp
    title: test/aoj/ntl/prime_factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_add_range_sum.test.cpp
    title: test/yosupo/data_structure/point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/set_xor-min.test.cpp
    title: test/yosupo/data_structure/set_xor-min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_range_sum.test.cpp
    title: test/yosupo/data_structure/static_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/unionfind.test.cpp
    title: test/yosupo/data_structure/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/graph/shortest_path.test.cpp
    title: test/yosupo/graph/shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/sample/many_a+b.test.cpp
    title: test/yosupo/sample/many_a+b.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.2/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#pragma GCC target(\"avx\")\n#pragma GCC optimize(\"O3\")\n\
    #pragma GCC optimize(\"unroll-loops\")\n#include \"template/template.hpp\"\nusing\
    \ ll = int64_t;\nusing ld = long double;\n#define FOR(i, m, n) for(int i = (m);\
    \ i < int(n); ++i)\n#define FORR(i, m, n) for(int i = (m)-1; i >= int(n); --i)\n\
    #define FORL(i, m, n) for(int64_t i = (m); i < int64_t(n); ++i)\n#define rep(i,\
    \ n) FOR(i, 0, n)\n#define repn(i, n) FOR(i, 1, n+1)\n#define repr(i, n) FORR(i,\
    \ n, 0)\n#define repnr(i, n) FORR(i, n+1, 1)\n#define all(s) (s).begin(), (s).end()\n\
    template<class T, class U>\nstd::istream &operator>>(std::istream &is, std::pair<T,\
    \ U> &p) { is >> p.first >> p.second; return is; }\ntemplate <class T>\nstd::istream\
    \ &operator>>(std::istream &is, std::vector<T> &v) { for (T &i : v) is>>i; return\
    \ is; }\ntemplate <class T, class U>\nstd::ostream &operator<<(std::ostream &os,\
    \ const std::pair<T, U> &p) {\n    return os<<'('<<p.first<< ','<<p.second<<')';\n\
    }\ntemplate <class T>\nstd::ostream &operator<<(std::ostream &os, const std::vector<T>\
    \ &v) {\n    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?\"\
    \":\" \")<<*it; } return os;\n}\ntemplate <class Head, class... Tail>\nvoid co(Head&&\
    \ head, Tail&&... tail) {\n    if constexpr(sizeof...(tail)==0) std::cout<<head<<'\\\
    n'; else std::cout<<head<<' ',co(forward<Tail>(tail)...);\n}\ntemplate <class\
    \ Head, class... Tail>\nvoid ce(Head&& head, Tail&&... tail) {\n    if constexpr(sizeof...(tail)==0)\
    \ std::cerr<<head<<'\\n'; else std::cerr<<head<<' ',ce(forward<Tail>(tail)...);\n\
    }\ntemplate<typename T, typename... Args>\nauto make_vector(T x, int arg, Args\
    \ ...args) {\n    if constexpr(sizeof...(args)==0) return std::vector<T>(arg,x);\
    \ else return std::vector(arg,make_vector<T>(x,args...));\n}\nvoid sonic() { std::ios::sync_with_stdio(false);\
    \ std::cin.tie(nullptr); }\nvoid setp(const int n) { std::cout<<std::fixed<<std::setprecision(n);\
    \ }\nvoid Yes(bool is_correct) { std::cout<<(is_correct?\"Yes\":\"No\")<<std::endl;\
    \ }\nvoid YES(bool is_correct) { std::cout<<(is_correct?\"YES\":\"NO\")<<std::endl;\
    \ }"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/template/atcoder.hpp
  requiredBy: []
  timestamp: '2022-02-08 12:58:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/convolution/convolution_mod.test.cpp
  - test/yosupo/data_structure/unionfind.test.cpp
  - test/yosupo/data_structure/point_add_range_sum.test.cpp
  - test/yosupo/data_structure/set_xor-min.test.cpp
  - test/yosupo/data_structure/static_rmq.test.cpp
  - test/yosupo/data_structure/static_range_sum.test.cpp
  - test/yosupo/graph/shortest_path.test.cpp
  - test/yosupo/sample/many_a+b.test.cpp
  - test/aoj/ntl/power.test.cpp
  - test/aoj/ntl/prime_factorize.test.cpp
  - test/aoj/dpl/longest_increasing_subsequense.test.cpp
  - test/aoj/dpl/bell.test.cpp
  - test/aoj/dpl/stirling.test.cpp
  - test/aoj/cgl/reflection.test.cpp
  - test/aoj/cgl/parallel_orthogonal.test.cpp
  - test/aoj/cgl/projection.test.cpp
  - test/aoj/cgl/intersection.test.cpp
  - test/aoj/cgl/cross_point.test.cpp
  - test/aoj/cgl/counter-clockwise.test.cpp
  - test/aoj/grl/hld.test.cpp
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
  - test/aoj/grl/dijkstra.test.cpp
  - test/aoj/grl/warshall_floyd.test.cpp
  - test/aoj/grl/bellman_ford.test.cpp
  - test/aoj/alds1/inversion_number.test.cpp
  - test/aoj/alds1/prime_numbers.test.cpp
  - test/aoj/dsl/ruq.test.cpp
  - test/aoj/dsl/rmq.test.cpp
documentation_of: lib/template/atcoder.hpp
layout: document
redirect_from:
- /library/lib/template/atcoder.hpp
- /library/lib/template/atcoder.hpp.html
title: lib/template/atcoder.hpp
---
