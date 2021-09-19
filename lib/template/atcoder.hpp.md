---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo/data_structure/static_range_sum.test.cpp
    title: test/yosupo/data_structure/static_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/unionfind.test.cpp
    title: test/yosupo/data_structure/unionfind.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/sample/many_a+b.test.cpp
    title: test/yosupo/sample/many_a+b.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.7/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\nusing ll = int64_t;\nusing ld = long\
    \ double;\n#define FOR(i, m, n) for(int i = (m); i < (n); ++i)\n#define FORR(i,\
    \ m, n) for(int i = (m)-1; i >= (n); --i)\n#define rep(i, n) FOR(i, 0, n)\n#define\
    \ repn(i, n) FOR(i, 1, n+1)\n#define repr(i, n) FORR(i, n, 0)\n#define repnr(i,\
    \ n) FORR(i, n+1, 1)\n#define all(s) (s).begin(), (s).end()\ntemplate <class T>\n\
    istream &operator>>(istream &is, vector<T> &v) { for (T &i : v) is>>i; return\
    \ is; }\ntemplate <class T>\nostream &operator<<(ostream &os, const vector<T>\
    \ &v) {\n    for (auto it=v.begin(); it!=v.end(); ++it) { os<<(it==v.begin()?\"\
    \":\" \")<<*it; } return os;\n}\ntemplate <class Head, class... Tail>\nvoid co(Head&&\
    \ head, Tail&&... tail) {\n    if constexpr(sizeof...(tail)==0) cout<<head<<'\\\
    n'; else cout<<head<<' ',co(forward<Tail>(tail)...);\n}\ntemplate <class Head,\
    \ class... Tail>\nvoid ce(Head&& head, Tail&&... tail) {\n    if constexpr(sizeof...(tail)==0)\
    \ cerr<<head<<'\\n'; else cerr<<head<<' ',ce(forward<Tail>(tail)...);\n}\ntemplate<typename\
    \ T, typename... Args>\nauto make_vector(T x, int arg, Args ...args) {\n    if\
    \ constexpr(sizeof...(args)==0) return vector<T>(arg, x); else return vector(arg,make_vector<T>(x,\
    \ args...));\n}\nvoid sonic() { ios::sync_with_stdio(false); cin.tie(nullptr);\
    \ }\nvoid setp(const int n) { cout << fixed << setprecision(n); }"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/template/atcoder.hpp
  requiredBy: []
  timestamp: '2021-09-19 05:28:53+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo/sample/many_a+b.test.cpp
  - test/yosupo/data_structure/static_range_sum.test.cpp
  - test/yosupo/data_structure/unionfind.test.cpp
  - test/yosupo/data_structure/static_rmq.test.cpp
documentation_of: lib/template/atcoder.hpp
layout: document
redirect_from:
- /library/lib/template/atcoder.hpp
- /library/lib/template/atcoder.hpp.html
title: lib/template/atcoder.hpp
---
