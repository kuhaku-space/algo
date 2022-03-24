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
  code: "#include \"template/template.hpp\"\r\n\r\ntemplate <class Key, class Value\
    \ = void>\r\nstruct radix_heap {\r\n  private:\r\n    struct _node {\r\n     \
    \   using pointer = _node*;\r\n        Key key;\r\n        Value value;\r\n  \
    \      int index;\r\n\r\n        constexpr _node(Key _key, Value _value) : key(_key),\
    \ value(_value), index() {}\r\n        constexpr _node(Key _key, Value _value,\
    \ int _index)\r\n            : key(_key), value(_value), index(_index) {}\r\n\r\
    \n        constexpr bool operator<(const _node& rhs) const { return this->value\
    \ < rhs.value; }\r\n\r\n        constexpr auto get_pair() const { return make_pair(key,\
    \ value); }\r\n    };\r\n\r\n  public:\r\n    using node_pointer = typename _node::pointer;\r\
    \n\r\n    radix_heap() : v{}, _last(), _size() {}\r\n\r\n    constexpr int size()\
    \ const { return this->_size; }\r\n    constexpr bool empty() const { return this->_size\
    \ == 0; }\r\n\r\n    auto push(Key key, Value value) {\r\n        assert(value\
    \ >= this->_last);\r\n        ++this->_size;\r\n        auto node = new _node(key,\
    \ value, this->find_bucket(value ^ this->_last));\r\n        this->v[node->index].emplace(node);\r\
    \n        return node;\r\n    }\r\n    auto emplace(Key key, Value value) { return\
    \ this->push(key, value); }\r\n\r\n    auto top() {\r\n        if (this->v[0].empty())\
    \ this->relocate();\r\n        return (*this->v[0].begin())->get_pair();\r\n \
    \   }\r\n\r\n    void pop() {\r\n        assert(this->_size);\r\n        if (this->v[0].empty())\
    \ this->relocate();\r\n        this->v[0].erase(this->v[0].begin());\r\n     \
    \   --this->_size;\r\n    }\r\n\r\n    void update(node_pointer node, Value value)\
    \ {\r\n        if (value < node->value)\r\n            node->value = value;\r\n\
    \        else\r\n            return;\r\n        this->v[node->index].erase(node);\r\
    \n        node->index = this->find_bucket(value ^ this->_last);\r\n        this->v[this->find_bucket(value\
    \ ^ this->_last)].emplace(node);\r\n    }\r\n\r\n  private:\r\n    std::unordered_set<node_pointer>\
    \ v[std::numeric_limits<Value>::digits + 1];\r\n    Value _last;\r\n    int _size;\r\
    \n\r\n    int find_bucket(Value value) const {\r\n        return value == 0 ?\
    \ 0 : std::numeric_limits<Value>::digits - this->clz(value);\r\n    }\r\n\r\n\
    \    template <class U>\r\n    int clz(U x) const {\r\n        static_assert(std::is_integral_v<U>);\r\
    \n        if constexpr (std::is_signed_v<U>)\r\n            return this->clz_unsigned(std::make_unsigned_t<U>(x))\
    \ - 1;\r\n        else\r\n            return this->clz_unsigned(x);\r\n    }\r\
    \n\r\n    template <class U>\r\n    int clz_unsigned(U x) const {\r\n        static_assert(std::is_integral_v<U>\
    \ && std::is_unsigned_v<U>);\r\n        if constexpr (std::is_same_v<U, unsigned\
    \ int>)\r\n            return __builtin_clz(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long>)\r\n            return __builtin_clzl(x);\r\n        else if\
    \ constexpr (std::is_same_v<U, unsigned long long>)\r\n            return __builtin_clzll(x);\r\
    \n        else\r\n            return -1;\r\n    }\r\n\r\n    void relocate() {\r\
    \n        int index = 1;\r\n        while (v[index].empty()) ++index;\r\n    \
    \    auto new_last = (*std::min_element(this->v[index].begin(), this->v[index].end(),\r\
    \n                                           [](const auto& a, const auto& b)\
    \ {\r\n                                               return a->value < b->value;\r\
    \n                                           }))\r\n                         \
    \   ->value;\r\n        for (auto node : this->v[index]) {\r\n            node->index\
    \ = this->find_bucket(node->value ^ new_last);\r\n            this->v[this->find_bucket(node->value\
    \ ^ new_last)].emplace(node);\r\n        }\r\n        this->_last = new_last;\r\
    \n        this->v[index].clear();\r\n    }\r\n};\r\n\r\ntemplate <class T>\r\n\
    struct radix_heap<T, void> {\r\n    radix_heap() : v{}, _last(), _size() {}\r\n\
    \r\n    constexpr int size() const { return this->_size; }\r\n    constexpr bool\
    \ empty() const { return this->_size == 0; }\r\n\r\n    void push(T x) {\r\n \
    \       assert(x >= this->_last);\r\n        ++this->_size;\r\n        this->v[this->find_bucket(x\
    \ ^ this->_last)].emplace_back(x);\r\n    }\r\n    void emplace(T x) { this->push(x);\
    \ }\r\n\r\n    T top() {\r\n        if (this->v[0].empty()) this->relocate();\r\
    \n        return this->_last;\r\n    }\r\n\r\n    void pop() {\r\n        assert(this->_size);\r\
    \n        if (this->v[0].empty()) this->relocate();\r\n        this->v[0].pop_back();\r\
    \n        --this->_size;\r\n    }\r\n\r\n  private:\r\n    std::vector<T> v[std::numeric_limits<T>::digits\
    \ + 1];\r\n    T _last;\r\n    int _size;\r\n\r\n    int find_bucket(T x) const\
    \ {\r\n        return x == 0 ? 0 : std::numeric_limits<T>::digits - this->clz(x);\r\
    \n    }\r\n\r\n    template <class U>\r\n    int clz(U x) const {\r\n        static_assert(std::is_integral_v<U>);\r\
    \n        if constexpr (std::is_signed_v<U>)\r\n            return this->clz_unsigned(std::make_unsigned_t<U>(x))\
    \ - 1;\r\n        else\r\n            return this->clz_unsigned(x);\r\n    }\r\
    \n\r\n    template <class U>\r\n    int clz_unsigned(U x) const {\r\n        static_assert(std::is_integral_v<U>\
    \ && std::is_unsigned_v<U>);\r\n        if constexpr (std::is_same_v<U, unsigned\
    \ int>)\r\n            return __builtin_clz(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long>)\r\n            return __builtin_clzl(x);\r\n        else if\
    \ constexpr (std::is_same_v<U, unsigned long long>)\r\n            return __builtin_clzll(x);\r\
    \n        else\r\n            return -1;\r\n    }\r\n\r\n    void relocate() {\r\
    \n        int index = 1;\r\n        while (v[index].empty()) ++index;\r\n    \
    \    auto new_last = *min_element(this->v[index].begin(), this->v[index].end());\r\
    \n        for (auto x : this->v[index]) { this->v[this->find_bucket(x ^ new_last)].emplace_back(x);\
    \ }\r\n        this->_last = new_last;\r\n        this->v[index].clear();\r\n\
    \    }\r\n};\r\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/heap/radix_heap.hpp
  requiredBy:
  - lib/graph/dijkstra_heap.hpp
  timestamp: '2022-03-20 16:30:00+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/grl/dijkstra_binary.test.cpp
  - test/aoj/grl/dijkstra_fibonacci.test.cpp
  - test/aoj/grl/dijkstra_radix.test.cpp
documentation_of: lib/heap/radix_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/radix_heap.hpp
- /library/lib/heap/radix_heap.hpp.html
title: lib/heap/radix_heap.hpp
---
