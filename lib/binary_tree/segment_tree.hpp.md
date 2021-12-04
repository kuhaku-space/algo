---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo/data_structure/static_rmq.test.cpp
    title: test/yosupo/data_structure/static_rmq.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
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
  code: "#include \"template/template.hpp\"\r\n\r\n/**\r\n * @brief \u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\r\n *\r\n * @tparam T \u8981\u7D20\u306E\u578B\r\n * @tparam\
    \ F \u95A2\u6570\u306E\u578B\r\n */\r\ntemplate <class T, class F>\r\nstruct segment_tree\
    \ {\r\n    int N;\r\n    const T e;\r\n    const F op;\r\n    vector<T> data;\r\
    \n\r\n    segment_tree() {}\r\n    /**\r\n     * @brief Construct a new segment\
    \ tree object\r\n     *\r\n     * @param _n length of array\r\n     * @param _e\
    \ identity element\r\n     * @param _op binary operation\r\n     */\r\n    segment_tree(int\
    \ _n, T _e, F &&_op) : e(_e), op(_op) { init(_n, _e); }\r\n    /**\r\n     * @brief\
    \ Construct a new segment tree object\r\n     *\r\n     * @param _n length of\
    \ array\r\n     * @param _e identity element\r\n     * @param _op binary operation\r\
    \n     */\r\n    segment_tree(int _n, T _e, const F &_op) : e(_e), op(_op) { this->init(_n,\
    \ _e); }\r\n\r\n    const T &operator[](int i) const { return this->data[i + N];\
    \ }\r\n    T at(int k) const { return this->operator[](k); }\r\n    T get(int\
    \ k) const { return this->operator[](k); }\r\n\r\n    void init(int n, const T\
    \ val) {\r\n        for (N = 1; N < n; N <<= 1) {}\r\n        this->data.assign(N\
    \ << 1, val);\r\n    }\r\n\r\n    template <class U>\r\n    void build(const vector<U>\
    \ &v) {\r\n        int n = v.size();\r\n        assert(n <= N);\r\n        for\
    \ (int i = 0; i < n; ++i) this->data[N + i] = T(v[i]);\r\n        for (int i =\
    \ N - 1; i >= 1; --i)\r\n            this->data[i] = this->op(this->data[i * 2],\
    \ this->data[i * 2 + 1]);\r\n    }\r\n\r\n    void update(int k, T val) {\r\n\
    \        assert(0 <= k && k < N);\r\n        this->data[k += N] = val;\r\n   \
    \     while ((k >>= 1) >= 1) this->data[k] = this->op(this->data[k * 2], this->data[k\
    \ * 2 + 1]);\r\n    }\r\n    void add(int k, T val) { this->update(k, val - this->at(k));\
    \ }\r\n\r\n    bool chmax(int k, T val) {\r\n        if (this->at(k) >= val) return\
    \ false;\r\n        this->update(k, val);\r\n        return true;\r\n    }\r\n\
    \    bool chmin(int k, T val) {\r\n        if (this->at(k) <= val) return false;\r\
    \n        this->update(k, val);\r\n        return true;\r\n    }\r\n\r\n    T\
    \ all_prod() const { return this->data[1]; }\r\n    T prod(int a, int b) const\
    \ {\r\n        assert(0 <= a && a <= N);\r\n        assert(0 <= b && b <= N);\r\
    \n        T l = e, r = e;\r\n        for (a += N, b += N; a < b; a >>= 1, b >>=\
    \ 1) {\r\n            if (a & 1) l = this->op(l, this->data[a++]);\r\n       \
    \     if (b & 1) r = this->op(this->data[--b], r);\r\n        }\r\n        return\
    \ this->op(l, r);\r\n    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/binary_tree/segment_tree.hpp
  requiredBy: []
  timestamp: '2021-11-25 18:19:34+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo/data_structure/static_rmq.test.cpp
documentation_of: lib/binary_tree/segment_tree.hpp
layout: document
redirect_from:
- /library/lib/binary_tree/segment_tree.hpp
- /library/lib/binary_tree/segment_tree.hpp.html
title: "\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
---
