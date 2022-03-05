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
    document_title: "\u91CD\u307F\u4ED8\u304D\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\
      \u9020"
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
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u91CD\u307F\u4ED8\u304D\
    \u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020\n *\n * @tparam T\n */\ntemplate\
    \ <class T>\nstruct weighted_union_find {\n    weighted_union_find() {}\n    weighted_union_find(int\
    \ size) : _data(size, -1), _weights(size) {}\n\n    int find(int k) {\n      \
    \  if (this->_data[k] < 0) return k;\n        auto par = this->find(this->_data[k]);\n\
    \        this->_weights[k] += this->_weights[this->_data[k]];\n        return\
    \ this->_data[k] = par;\n    }\n\n    T get_weight(int t) {\n        this->find(t);\n\
    \        return this->_weights[t];\n    }\n\n    bool unite(int x, int y, T w)\
    \ {\n        w += this->get_weight(x) - this->get_weight(y);\n        x = find(x),\
    \ y = find(y);\n        if (x == y) return false;\n        if (this->_data[x]\
    \ > this->_data[y]) {\n            swap(x, y);\n            w *= -1;\n       \
    \ }\n        this->_data[x] += this->_data[y];\n        this->_data[y] = x;\n\
    \        this->_weights[y] = w;\n        return true;\n    }\n\n    T diff(int\
    \ x, int y) { return this->get_weight(y) - this->get_weight(x); }\n\n  private:\n\
    \    std::vector<int> _data;\n    std::vector<T> _weights;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/weighted_union_find.hpp
  requiredBy: []
  timestamp: '2022-02-08 14:39:18+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/tree/weighted_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/weighted_union_find.hpp
- /library/lib/tree/weighted_union_find.hpp.html
title: "\u91CD\u307F\u4ED8\u304D\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
---
