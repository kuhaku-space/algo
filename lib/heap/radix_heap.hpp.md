---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/heap/radix_heap.hpp\"\n#include <algorithm>\r\n#include\
    \ <cassert>\r\n#include <limits>\r\n#include <type_traits>\r\n#include <unordered_set>\r\
    \n#include <vector>\r\n\r\ntemplate <class Key, class Value = void>\r\nstruct\
    \ radix_heap {\r\n  private:\r\n    struct _node {\r\n        using pointer =\
    \ _node *;\r\n        Key key;\r\n        Value value;\r\n        int index;\r\
    \n\r\n        constexpr _node(Key _key, Value _value) : key(_key), value(_value),\
    \ index() {}\r\n        constexpr _node(Key _key, Value _value, int _index)\r\n\
    \            : key(_key), value(_value), index(_index) {}\r\n\r\n        constexpr\
    \ bool operator<(const _node &rhs) const { return value < rhs.value; }\r\n\r\n\
    \        constexpr auto get_pair() const { return std::make_pair(key, value);\
    \ }\r\n    };\r\n\r\n  public:\r\n    using key_type = Key;\r\n    using value_type\
    \ = Value;\r\n    using node_ptr = typename _node::pointer;\r\n\r\n    radix_heap()\
    \ : data{}, _last(), _size() {}\r\n\r\n    constexpr int size() const { return\
    \ _size; }\r\n    constexpr bool empty() const { return _size == 0; }\r\n\r\n\
    \    auto push(Key key, Value value) {\r\n        assert(value >= _last);\r\n\
    \        ++_size;\r\n        auto node = new _node(key, value, find_bucket(value\
    \ ^ _last));\r\n        data[node->index].emplace(node);\r\n        return node;\r\
    \n    }\r\n    auto emplace(Key key, Value value) { return push(key, value); }\r\
    \n\r\n    auto top() {\r\n        if (data[0].empty()) relocate();\r\n       \
    \ return (*data[0].begin())->get_pair();\r\n    }\r\n\r\n    void pop() {\r\n\
    \        assert(_size);\r\n        if (data[0].empty()) relocate();\r\n      \
    \  data[0].erase(data[0].begin());\r\n        --_size;\r\n    }\r\n\r\n    void\
    \ update(node_ptr node, Value value) {\r\n        if (value < node->value) node->value\
    \ = value;\r\n        else return;\r\n        data[node->index].erase(node);\r\
    \n        node->index = find_bucket(value ^ _last);\r\n        data[find_bucket(value\
    \ ^ _last)].emplace(node);\r\n    }\r\n\r\n  private:\r\n    std::unordered_set<node_ptr>\
    \ data[std::numeric_limits<Value>::digits + 1];\r\n    Value _last;\r\n    int\
    \ _size;\r\n\r\n    int find_bucket(Value value) const {\r\n        return value\
    \ == 0 ? 0 : std::numeric_limits<Value>::digits - clz(value);\r\n    }\r\n\r\n\
    \    template <class U>\r\n    int clz(U x) const {\r\n        static_assert(std::is_integral_v<U>);\r\
    \n        if constexpr (std::is_signed_v<U>) return clz_unsigned(std::make_unsigned_t<U>(x))\
    \ - 1;\r\n        else return clz_unsigned(x);\r\n    }\r\n\r\n    template <class\
    \ U>\r\n    int clz_unsigned(U x) const {\r\n        static_assert(std::is_integral_v<U>\
    \ && std::is_unsigned_v<U>);\r\n        if constexpr (std::is_same_v<U, unsigned\
    \ int>) return __builtin_clz(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long>) return __builtin_clzl(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long long>) return __builtin_clzll(x);\r\n        else return -1;\r\
    \n    }\r\n\r\n    void relocate() {\r\n        int index = 1;\r\n        while\
    \ (data[index].empty()) ++index;\r\n        auto new_last =\r\n            (*std::min_element(data[index].begin(),\
    \ data[index].end(),\r\n                               [](const auto &a, const\
    \ auto &b) { return a->value < b->value; }))\r\n                ->value;\r\n \
    \       for (auto node : data[index]) {\r\n            node->index = find_bucket(node->value\
    \ ^ new_last);\r\n            data[find_bucket(node->value ^ new_last)].emplace(node);\r\
    \n        }\r\n        _last = new_last;\r\n        data[index].clear();\r\n \
    \   }\r\n};\r\n\r\ntemplate <class T>\r\nstruct radix_heap<T, void> {\r\n    radix_heap()\
    \ : data{}, _last(), _size() {}\r\n\r\n    constexpr int size() const { return\
    \ _size; }\r\n    constexpr bool empty() const { return _size == 0; }\r\n\r\n\
    \    void push(T x) {\r\n        assert(x >= _last);\r\n        ++_size;\r\n \
    \       data[find_bucket(x ^ _last)].emplace_back(x);\r\n    }\r\n    void emplace(T\
    \ x) { push(x); }\r\n\r\n    T top() {\r\n        if (data[0].empty()) relocate();\r\
    \n        return _last;\r\n    }\r\n\r\n    void pop() {\r\n        assert(_size);\r\
    \n        if (data[0].empty()) relocate();\r\n        data[0].pop_back();\r\n\
    \        --_size;\r\n    }\r\n\r\n  private:\r\n    std::vector<T> data[std::numeric_limits<T>::digits\
    \ + 1];\r\n    T _last;\r\n    int _size;\r\n\r\n    int find_bucket(T x) const\
    \ { return x == 0 ? 0 : std::numeric_limits<T>::digits - clz(x); }\r\n\r\n   \
    \ template <class U>\r\n    int clz(U x) const {\r\n        static_assert(std::is_integral_v<U>);\r\
    \n        if constexpr (std::is_signed_v<U>) return clz_unsigned(std::make_unsigned_t<U>(x))\
    \ - 1;\r\n        else return clz_unsigned(x);\r\n    }\r\n\r\n    template <class\
    \ U>\r\n    int clz_unsigned(U x) const {\r\n        static_assert(std::is_integral_v<U>\
    \ && std::is_unsigned_v<U>);\r\n        if constexpr (std::is_same_v<U, unsigned\
    \ int>) return __builtin_clz(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long>) return __builtin_clzl(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long long>) return __builtin_clzll(x);\r\n        else return -1;\r\
    \n    }\r\n\r\n    void relocate() {\r\n        int index = 1;\r\n        while\
    \ (data[index].empty()) ++index;\r\n        auto new_last = *min_element(data[index].begin(),\
    \ data[index].end());\r\n        for (auto x : data[index]) { data[find_bucket(x\
    \ ^ new_last)].emplace_back(x); }\r\n        _last = new_last;\r\n        data[index].clear();\r\
    \n    }\r\n};\r\n"
  code: "#include <algorithm>\r\n#include <cassert>\r\n#include <limits>\r\n#include\
    \ <type_traits>\r\n#include <unordered_set>\r\n#include <vector>\r\n\r\ntemplate\
    \ <class Key, class Value = void>\r\nstruct radix_heap {\r\n  private:\r\n   \
    \ struct _node {\r\n        using pointer = _node *;\r\n        Key key;\r\n \
    \       Value value;\r\n        int index;\r\n\r\n        constexpr _node(Key\
    \ _key, Value _value) : key(_key), value(_value), index() {}\r\n        constexpr\
    \ _node(Key _key, Value _value, int _index)\r\n            : key(_key), value(_value),\
    \ index(_index) {}\r\n\r\n        constexpr bool operator<(const _node &rhs) const\
    \ { return value < rhs.value; }\r\n\r\n        constexpr auto get_pair() const\
    \ { return std::make_pair(key, value); }\r\n    };\r\n\r\n  public:\r\n    using\
    \ key_type = Key;\r\n    using value_type = Value;\r\n    using node_ptr = typename\
    \ _node::pointer;\r\n\r\n    radix_heap() : data{}, _last(), _size() {}\r\n\r\n\
    \    constexpr int size() const { return _size; }\r\n    constexpr bool empty()\
    \ const { return _size == 0; }\r\n\r\n    auto push(Key key, Value value) {\r\n\
    \        assert(value >= _last);\r\n        ++_size;\r\n        auto node = new\
    \ _node(key, value, find_bucket(value ^ _last));\r\n        data[node->index].emplace(node);\r\
    \n        return node;\r\n    }\r\n    auto emplace(Key key, Value value) { return\
    \ push(key, value); }\r\n\r\n    auto top() {\r\n        if (data[0].empty())\
    \ relocate();\r\n        return (*data[0].begin())->get_pair();\r\n    }\r\n\r\
    \n    void pop() {\r\n        assert(_size);\r\n        if (data[0].empty()) relocate();\r\
    \n        data[0].erase(data[0].begin());\r\n        --_size;\r\n    }\r\n\r\n\
    \    void update(node_ptr node, Value value) {\r\n        if (value < node->value)\
    \ node->value = value;\r\n        else return;\r\n        data[node->index].erase(node);\r\
    \n        node->index = find_bucket(value ^ _last);\r\n        data[find_bucket(value\
    \ ^ _last)].emplace(node);\r\n    }\r\n\r\n  private:\r\n    std::unordered_set<node_ptr>\
    \ data[std::numeric_limits<Value>::digits + 1];\r\n    Value _last;\r\n    int\
    \ _size;\r\n\r\n    int find_bucket(Value value) const {\r\n        return value\
    \ == 0 ? 0 : std::numeric_limits<Value>::digits - clz(value);\r\n    }\r\n\r\n\
    \    template <class U>\r\n    int clz(U x) const {\r\n        static_assert(std::is_integral_v<U>);\r\
    \n        if constexpr (std::is_signed_v<U>) return clz_unsigned(std::make_unsigned_t<U>(x))\
    \ - 1;\r\n        else return clz_unsigned(x);\r\n    }\r\n\r\n    template <class\
    \ U>\r\n    int clz_unsigned(U x) const {\r\n        static_assert(std::is_integral_v<U>\
    \ && std::is_unsigned_v<U>);\r\n        if constexpr (std::is_same_v<U, unsigned\
    \ int>) return __builtin_clz(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long>) return __builtin_clzl(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long long>) return __builtin_clzll(x);\r\n        else return -1;\r\
    \n    }\r\n\r\n    void relocate() {\r\n        int index = 1;\r\n        while\
    \ (data[index].empty()) ++index;\r\n        auto new_last =\r\n            (*std::min_element(data[index].begin(),\
    \ data[index].end(),\r\n                               [](const auto &a, const\
    \ auto &b) { return a->value < b->value; }))\r\n                ->value;\r\n \
    \       for (auto node : data[index]) {\r\n            node->index = find_bucket(node->value\
    \ ^ new_last);\r\n            data[find_bucket(node->value ^ new_last)].emplace(node);\r\
    \n        }\r\n        _last = new_last;\r\n        data[index].clear();\r\n \
    \   }\r\n};\r\n\r\ntemplate <class T>\r\nstruct radix_heap<T, void> {\r\n    radix_heap()\
    \ : data{}, _last(), _size() {}\r\n\r\n    constexpr int size() const { return\
    \ _size; }\r\n    constexpr bool empty() const { return _size == 0; }\r\n\r\n\
    \    void push(T x) {\r\n        assert(x >= _last);\r\n        ++_size;\r\n \
    \       data[find_bucket(x ^ _last)].emplace_back(x);\r\n    }\r\n    void emplace(T\
    \ x) { push(x); }\r\n\r\n    T top() {\r\n        if (data[0].empty()) relocate();\r\
    \n        return _last;\r\n    }\r\n\r\n    void pop() {\r\n        assert(_size);\r\
    \n        if (data[0].empty()) relocate();\r\n        data[0].pop_back();\r\n\
    \        --_size;\r\n    }\r\n\r\n  private:\r\n    std::vector<T> data[std::numeric_limits<T>::digits\
    \ + 1];\r\n    T _last;\r\n    int _size;\r\n\r\n    int find_bucket(T x) const\
    \ { return x == 0 ? 0 : std::numeric_limits<T>::digits - clz(x); }\r\n\r\n   \
    \ template <class U>\r\n    int clz(U x) const {\r\n        static_assert(std::is_integral_v<U>);\r\
    \n        if constexpr (std::is_signed_v<U>) return clz_unsigned(std::make_unsigned_t<U>(x))\
    \ - 1;\r\n        else return clz_unsigned(x);\r\n    }\r\n\r\n    template <class\
    \ U>\r\n    int clz_unsigned(U x) const {\r\n        static_assert(std::is_integral_v<U>\
    \ && std::is_unsigned_v<U>);\r\n        if constexpr (std::is_same_v<U, unsigned\
    \ int>) return __builtin_clz(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long>) return __builtin_clzl(x);\r\n        else if constexpr (std::is_same_v<U,\
    \ unsigned long long>) return __builtin_clzll(x);\r\n        else return -1;\r\
    \n    }\r\n\r\n    void relocate() {\r\n        int index = 1;\r\n        while\
    \ (data[index].empty()) ++index;\r\n        auto new_last = *min_element(data[index].begin(),\
    \ data[index].end());\r\n        for (auto x : data[index]) { data[find_bucket(x\
    \ ^ new_last)].emplace_back(x); }\r\n        _last = new_last;\r\n        data[index].clear();\r\
    \n    }\r\n};\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/heap/radix_heap.hpp
  requiredBy: []
  timestamp: '2024-05-03 20:53:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/heap/radix_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/radix_heap.hpp
- /library/lib/heap/radix_heap.hpp.html
title: lib/heap/radix_heap.hpp
---
