---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dsl/weighted_union_find.test.cpp
    title: test/aoj/dsl/weighted_union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u91CD\u307F\u4ED8\u304D\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\
      \u9020"
    links: []
  bundledCode: "#line 1 \"lib/tree/weighted_union_find.hpp\"\n#include <utility>\n\
    #include <vector>\n\n/**\n * @brief \u91CD\u307F\u4ED8\u304D\u7D20\u96C6\u5408\
    \u30C7\u30FC\u30BF\u69CB\u9020\n *\n * @tparam T\n */\ntemplate <class T>\nstruct\
    \ weighted_union_find {\n    weighted_union_find() {}\n    weighted_union_find(int\
    \ size) : _data(size, -1), _weights(size) {}\n\n    int find(int k) {\n      \
    \  if (_data[k] < 0) return k;\n        int par = find(_data[k]);\n        _weights[k]\
    \ += _weights[_data[k]];\n        return _data[k] = par;\n    }\n\n    T get_weight(int\
    \ t) {\n        find(t);\n        return _weights[t];\n    }\n\n    /**\n    \
    \ * @brief v[y] = v[x] + w\n     *\n     * @param x\n     * @param y\n     * @param\
    \ w\n     * @return true unite correctly\n     * @return false already united\n\
    \     */\n    bool unite(int x, int y, T w) {\n        w += get_weight(x) - get_weight(y);\n\
    \        x = find(x), y = find(y);\n        if (x == y) return false;\n      \
    \  if (_data[x] > _data[y]) {\n            std::swap(x, y);\n            w *=\
    \ -1;\n        }\n        _data[x] += _data[y];\n        _data[y] = x;\n     \
    \   _weights[y] = w;\n        return true;\n    }\n\n    bool same(int x, int\
    \ y) { return find(x) == find(y); }\n    bool is_same(int x, int y) { return same(x,\
    \ y); }\n\n    /**\n     * @brief get diff between x and y\n     *\n     * @param\
    \ x\n     * @param y\n     * @return T v[y] - v[x]\n     */\n    T diff(int x,\
    \ int y) { return get_weight(y) - get_weight(x); }\n    T get_diff(int x, int\
    \ y) { return diff(x, y); }\n\n  private:\n    std::vector<int> _data;\n    std::vector<T>\
    \ _weights;\n};\n"
  code: "#include <utility>\n#include <vector>\n\n/**\n * @brief \u91CD\u307F\u4ED8\
    \u304D\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020\n *\n * @tparam T\n */\n\
    template <class T>\nstruct weighted_union_find {\n    weighted_union_find() {}\n\
    \    weighted_union_find(int size) : _data(size, -1), _weights(size) {}\n\n  \
    \  int find(int k) {\n        if (_data[k] < 0) return k;\n        int par = find(_data[k]);\n\
    \        _weights[k] += _weights[_data[k]];\n        return _data[k] = par;\n\
    \    }\n\n    T get_weight(int t) {\n        find(t);\n        return _weights[t];\n\
    \    }\n\n    /**\n     * @brief v[y] = v[x] + w\n     *\n     * @param x\n  \
    \   * @param y\n     * @param w\n     * @return true unite correctly\n     * @return\
    \ false already united\n     */\n    bool unite(int x, int y, T w) {\n       \
    \ w += get_weight(x) - get_weight(y);\n        x = find(x), y = find(y);\n   \
    \     if (x == y) return false;\n        if (_data[x] > _data[y]) {\n        \
    \    std::swap(x, y);\n            w *= -1;\n        }\n        _data[x] += _data[y];\n\
    \        _data[y] = x;\n        _weights[y] = w;\n        return true;\n    }\n\
    \n    bool same(int x, int y) { return find(x) == find(y); }\n    bool is_same(int\
    \ x, int y) { return same(x, y); }\n\n    /**\n     * @brief get diff between\
    \ x and y\n     *\n     * @param x\n     * @param y\n     * @return T v[y] - v[x]\n\
    \     */\n    T diff(int x, int y) { return get_weight(y) - get_weight(x); }\n\
    \    T get_diff(int x, int y) { return diff(x, y); }\n\n  private:\n    std::vector<int>\
    \ _data;\n    std::vector<T> _weights;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/tree/weighted_union_find.hpp
  requiredBy: []
  timestamp: '2024-01-23 17:38:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/dsl/weighted_union_find.test.cpp
documentation_of: lib/tree/weighted_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/weighted_union_find.hpp
- /library/lib/tree/weighted_union_find.hpp.html
title: "\u91CD\u307F\u4ED8\u304D\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020"
---
