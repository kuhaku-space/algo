---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/segment_tree/RAQ.hpp
    title: lib/segment_tree/RAQ.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.1/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n * @tparam\
    \ F \u95A2\u6570\u306E\u578B\r\n */\r\ntemplate <class T>\r\nstruct segment_tree\
    \ {\r\n    int N;\r\n    const T e;\r\n    vector<T> data;\r\n\r\n    segment_tree()\
    \ {}\r\n    segment_tree(int _n, T _e) : e(_e) { this->init(_n, _e); }\r\n\r\n\
    \    const T &operator[](int i) const { return this->data[i + this->N]; }\r\n\
    \    T at(int k) const { return this->operator[](k); }\r\n    T get(int k) const\
    \ { return this->operator[](k); }\r\n\r\n    void init(int n, const T val) {\r\
    \n        for (this->N = 1; this->N < n; this->N <<= 1) {}\r\n        this->data.assign(this->N\
    \ << 1, val);\r\n    }\r\n\r\n    template <class U>\r\n    void build(const vector<U>\
    \ &v) {\r\n        for (int i = 0, n = v.size(); i < n; ++i) this->data[this->N\
    \ + i] = T(v[i]);\r\n        for (int i = this->N - 1; i >= 1; --i)\r\n      \
    \      this->data[i] = this->op(this->data[i * 2], this->data[i * 2 + 1]);\r\n\
    \    }\r\n\r\n    void apply(int k, T val) {\r\n        assert(0 <= k && k < this->N);\r\
    \n        k += this->N;\r\n        this->data[k] = f(val, this->data[k]);\r\n\
    \        while ((k >>= 1) >= 1) this->data[k] = this->op(this->data[k * 2], this->data[k\
    \ * 2 + 1]);\r\n    }\r\n\r\n    T all_prod() const { return this->data[1]; }\r\
    \n    T prod(int a, int b) const {\r\n        assert(0 <= a && b <= this->N);\r\
    \n        T l = e, r = e;\r\n        for (a += this->N, b += this->N; a < b; a\
    \ >>= 1, b >>= 1) {\r\n            if (a & 1) l = this->op(l, this->data[a++]);\r\
    \n            if (b & 1) r = this->op(this->data[--b], r);\r\n        }\r\n  \
    \      return this->op(l, r);\r\n    }\r\n\r\n  protected:\r\n    virtual T op(T\
    \ a, T b) const = 0;\r\n    virtual T f(T val, T x) const = 0;\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/segment_tree/segment_tree_virtual.hpp
  requiredBy:
  - lib/segment_tree/RAQ.hpp
  timestamp: '2021-12-28 06:14:56+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/segment_tree/segment_tree_virtual.hpp
layout: document
redirect_from:
- /library/lib/segment_tree/segment_tree_virtual.hpp
- /library/lib/segment_tree/segment_tree_virtual.hpp.html
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
