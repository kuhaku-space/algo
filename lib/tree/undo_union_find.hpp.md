---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/undo_union_find.test.cpp
    title: test/yosupo/data_structure/undo_union_find.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Undo\u53EF\u80FDUnion-Find"
    links:
    - https://ei1333.github.io/luzhiled/snippets/structure/union-find.html
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief Undo\u53EF\u80FDUnion-Find\n\
    \ * @details Implement (union by size)\n *\n * @see https://ei1333.github.io/luzhiled/snippets/structure/union-find.html\n\
    \ */\nstruct undo_union_find {\n    undo_union_find() : data(), history() {}\n\
    \    undo_union_find(int _n) : data(_n, -1), history() {}\n\n    int root(int\
    \ x) { return this->data[x] < 0 ? x : this->data[x] = this->root(this->data[x]);\
    \ }\n    int get_root(int k) { return this->root(k); }\n\n    bool is_root(int\
    \ k) const { return this->data[0] < 0; }\n\n    bool same(int x, int y) { return\
    \ this->root(x) == this->root(y); }\n    bool is_same(int x, int y) { return this->same(x,\
    \ y); }\n\n    int size(int k) { return -this->data[this->root(k)]; }\n    int\
    \ get_size(int k) { return this->size(k); }\n\n    bool unite(int x, int y) {\n\
    \        x = this->root(x), y = this->root(y);\n        this->history.emplace(x,\
    \ this->data[x]);\n        this->history.emplace(y, this->data[y]);\n        if\
    \ (x == y) return false;\n        if (this->data[x] > this->data[y]) std::swap(x,\
    \ y);\n        this->data[x] += this->data[y];\n        this->data[y] = x;\n \
    \       return true;\n    }\n\n    void undo() {\n        this->data[this->history.top().first]\
    \ = this->history.top().second;\n        this->history.pop();\n        this->data[this->history.top().first]\
    \ = this->history.top().second;\n        this->history.pop();\n    }\n\n    int\
    \ snapshot() const { return this->history.size(); }\n\n    void rollback(int x\
    \ = 0) {\n        while ((int)(this->history.size()) > x) this->undo();\n    }\n\
    \n  private:\n    std::vector<int> data;\n    std::stack<std::pair<int, int>>\
    \ history;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/undo_union_find.hpp
  requiredBy: []
  timestamp: '2023-05-22 20:02:34+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/data_structure/undo_union_find.test.cpp
documentation_of: lib/tree/undo_union_find.hpp
layout: document
redirect_from:
- /library/lib/tree/undo_union_find.hpp
- /library/lib/tree/undo_union_find.hpp.html
title: "Undo\u53EF\u80FDUnion-Find"
---
