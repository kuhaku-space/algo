---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/graph/dijkstra_heap.hpp
    title: "\u30C0\u30A4\u30AF\u30B9\u30C8\u30E9\u6CD5\uFF08\u30D2\u30FC\u30D7\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_binary.test.cpp
    title: test/aoj/grl/dijkstra_binary.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_fibonacci.test.cpp
    title: test/aoj/grl/dijkstra_fibonacci.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/grl/dijkstra_radix.test.cpp
    title: test/aoj/grl/dijkstra_radix.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E8C\u5206\u30D2\u30FC\u30D7"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.11/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief \u4E8C\u5206\u30D2\u30FC\
    \u30D7\n *\n * @tparam Key \u30AD\u30FC\u306E\u578B\n * @tparam Value \u5024\u306E\
    \u578B\n * @tparam Comp \u6BD4\u8F03\u30AA\u30D6\u30B8\u30A7\u30AF\u30C8\n */\n\
    template <class Key, class Value, class Comp = std::less<>>\nstruct binary_heap\
    \ {\n  private:\n    struct _node {\n        using pointer = _node *;\n\n    \
    \    Key key;\n        Value value;\n        int index;\n\n        constexpr _node(Key\
    \ _key, Value _value) : key(_key), value(_value), index() {}\n\n        constexpr\
    \ bool operator<(const _node &rhs) const { return this->value < rhs.value; }\n\
    \n        constexpr std::pair<Key, Value> get_pair() const { return std::make_pair(key,\
    \ value); }\n        constexpr int get_index() const { return this->index; }\n\
    \        constexpr void set_index(int new_index) { this->index = new_index; }\n\
    \    };\n\n  public:\n    using node_ptr = typename _node::pointer;\n\n    binary_heap()\
    \ : _size(), nodes(1), comp() {}\n\n    std::pair<Key, Value> top() const { return\
    \ this->nodes[1]->get_pair(); }\n    constexpr int size() const { return this->_size;\
    \ }\n    constexpr bool empty() const { return this->size() == 0; }\n\n    node_ptr\
    \ push(Key key, Value value) {\n        auto node = new _node(key, value);\n \
    \       this->nodes.emplace_back(node);\n\n        int index = this->increment_size();\n\
    \        while (index > 1 && comp(this->nodes[index >> 1]->value, this->nodes[index]->value))\
    \ {\n            swap(this->nodes[index], this->nodes[index >> 1]);\n        \
    \    this->nodes[index]->set_index(index);\n            index >>= 1;\n       \
    \ }\n        this->nodes[index]->set_index(index);\n\n        return node;\n \
    \   }\n    node_ptr emplace(Key key, Value value) { return this->push(key, value);\
    \ }\n\n    void pop() {\n        this->nodes[1] = this->nodes[this->decrement_size()];\n\
    \        this->nodes.pop_back();\n\n        int index = 1 << 1;\n        while\
    \ (index <= this->size()) {\n            if (index < this->size() &&\n       \
    \         comp(this->nodes[index]->value, this->nodes[index + 1]->value))\n  \
    \              ++index;\n            if (comp(this->nodes[index]->value, this->nodes[index\
    \ >> 1]->value)) break;\n            swap(this->nodes[index >> 1], this->nodes[index]);\n\
    \            this->nodes[index >> 1]->set_index(index >> 1);\n            index\
    \ <<= 1;\n        }\n        this->nodes[index >> 1]->set_index(index >> 1);\n\
    \    }\n\n    void update(node_ptr node, Value value) {\n        if (comp(node->value,\
    \ value)) node->value = value;\n        else return;\n        int index = node->get_index();\n\
    \        while (index > 1 && comp(this->nodes[index >> 1]->value, this->nodes[index]->value))\
    \ {\n            swap(this->nodes[index], this->nodes[index >> 1]);\n        \
    \    this->nodes[index]->set_index(index);\n            index >>= 1;\n       \
    \ }\n        this->nodes[index]->set_index(index);\n    }\n\n  private:\n    int\
    \ _size;\n    std::vector<node_ptr> nodes;\n    Comp comp;\n\n    constexpr int\
    \ increment_size() { return ++(this->_size); }\n    constexpr int decrement_size()\
    \ { return (this->_size)--; }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/heap/binary_heap.hpp
  requiredBy:
  - lib/graph/dijkstra_heap.hpp
  timestamp: '2022-07-11 16:46:27+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra_binary.test.cpp
  - test/aoj/grl/dijkstra_radix.test.cpp
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
documentation_of: lib/heap/binary_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/binary_heap.hpp
- /library/lib/heap/binary_heap.hpp.html
title: "\u4E8C\u5206\u30D2\u30FC\u30D7"
---
