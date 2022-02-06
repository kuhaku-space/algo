---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: lib/graph/graph.hpp
    title: lib/graph/graph.hpp
  - icon: ':question:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/graph/dijkstra_heap.hpp\"\n#include <graph/graph.hpp>\n\
    #include <template/template.hpp>\n\ntemplate <class T>\nstruct heap {\n    heap(int\
    \ n) : _size(), v(1), u(n) {}\n\n    auto top() const { return this->v[1]; }\n\
    \    int size() const { return this->_size; }\n    bool empty() const { return\
    \ this->_size == 0; }\n\n    void push(int a, T b) {\n        if (this->u[a])\
    \ {\n            this->update(a, b);\n            return;\n        }\n       \
    \ this->u[a] = ++(this->_size);\n        this->v.emplace_back(a, b);\n\n     \
    \   int idx = this->_size;\n        while (idx > 1 && this->v[idx].second < this->v[idx\
    \ >> 1].second) {\n            swap(this->u[a], this->u[this->v[idx >> 1].first]);\n\
    \            swap(this->v[idx], this->v[idx >> 1]);\n            idx >>= 1;\n\
    \        }\n    }\n    void emplace(int a, T b) { this->push(a, b); }\n\n    void\
    \ pop() {\n        this->u[this->v[this->_size].first] = 1;\n        this->v[1]\
    \ = this->v[(this->_size)--];\n        this->v.pop_back();\n\n        int idx\
    \ = 1 << 1;\n        while (idx <= this->_size) {\n            if (idx < this->_size\
    \ && this->v[idx + 1].second < this->v[idx].second) ++idx;\n            if (this->v[idx\
    \ >> 1].second < this->v[idx].second) break;\n            swap(this->u[this->v[idx\
    \ >> 1].first], this->u[this->v[idx].first]);\n            swap(this->v[idx >>\
    \ 1], this->v[idx]);\n            idx <<= 1;\n        }\n    }\n\n    void update(int\
    \ a, T b) {\n        if (b < this->v[this->u[a]].second) {\n            this->v[this->u[a]].second\
    \ = b;\n            int idx = this->u[a];\n            while (idx > 1 && this->v[idx].second\
    \ < this->v[idx >> 1].second) {\n                swap(this->u[a], this->u[this->v[idx\
    \ >> 1].first]);\n                swap(this->v[idx], this->v[idx >> 1]);\n   \
    \             idx >>= 1;\n            }\n        }\n    }\n\n  private:\n    int\
    \ _size;\n    std::vector<pair<int, T>> v;\n    std::vector<int> u;\n};\n\ntemplate\
    \ <class T>\nstd::vector<T> dijkstra(const Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max())\
    \ {\n    struct _edge {\n        int to;\n        T dist;\n        constexpr _edge()\
    \ : to(), dist() {}\n        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist)\
    \ {}\n        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist;\
    \ }\n        bool operator>(const _edge &rhs) const { return rhs < *this; }\n\
    \    };\n    std::vector<T> dists(g.size(), inf);\n    heap<T> p_que(g.size());\n\
    \    dists[s] = T();\n    p_que.emplace(s, T());\n    while (!p_que.empty()) {\n\
    \        auto [to, dist] = p_que.top();\n        p_que.pop();\n        if (dists[to]\
    \ < dist) continue;\n        for (auto &i : g[to]) {\n            if (chmin(dists[i.to],\
    \ dist + i.dist)) p_que.emplace(i.to, dist + i.dist);\n        }\n    }\n    return\
    \ dists;\n}\n"
  code: "#include <graph/graph.hpp>\n#include <template/template.hpp>\n\ntemplate\
    \ <class T>\nstruct heap {\n    heap(int n) : _size(), v(1), u(n) {}\n\n    auto\
    \ top() const { return this->v[1]; }\n    int size() const { return this->_size;\
    \ }\n    bool empty() const { return this->_size == 0; }\n\n    void push(int\
    \ a, T b) {\n        if (this->u[a]) {\n            this->update(a, b);\n    \
    \        return;\n        }\n        this->u[a] = ++(this->_size);\n        this->v.emplace_back(a,\
    \ b);\n\n        int idx = this->_size;\n        while (idx > 1 && this->v[idx].second\
    \ < this->v[idx >> 1].second) {\n            swap(this->u[a], this->u[this->v[idx\
    \ >> 1].first]);\n            swap(this->v[idx], this->v[idx >> 1]);\n       \
    \     idx >>= 1;\n        }\n    }\n    void emplace(int a, T b) { this->push(a,\
    \ b); }\n\n    void pop() {\n        this->u[this->v[this->_size].first] = 1;\n\
    \        this->v[1] = this->v[(this->_size)--];\n        this->v.pop_back();\n\
    \n        int idx = 1 << 1;\n        while (idx <= this->_size) {\n          \
    \  if (idx < this->_size && this->v[idx + 1].second < this->v[idx].second) ++idx;\n\
    \            if (this->v[idx >> 1].second < this->v[idx].second) break;\n    \
    \        swap(this->u[this->v[idx >> 1].first], this->u[this->v[idx].first]);\n\
    \            swap(this->v[idx >> 1], this->v[idx]);\n            idx <<= 1;\n\
    \        }\n    }\n\n    void update(int a, T b) {\n        if (b < this->v[this->u[a]].second)\
    \ {\n            this->v[this->u[a]].second = b;\n            int idx = this->u[a];\n\
    \            while (idx > 1 && this->v[idx].second < this->v[idx >> 1].second)\
    \ {\n                swap(this->u[a], this->u[this->v[idx >> 1].first]);\n   \
    \             swap(this->v[idx], this->v[idx >> 1]);\n                idx >>=\
    \ 1;\n            }\n        }\n    }\n\n  private:\n    int _size;\n    std::vector<pair<int,\
    \ T>> v;\n    std::vector<int> u;\n};\n\ntemplate <class T>\nstd::vector<T> dijkstra(const\
    \ Graph<T> &g, int s = 0, T inf = std::numeric_limits<T>::max()) {\n    struct\
    \ _edge {\n        int to;\n        T dist;\n        constexpr _edge() : to(),\
    \ dist() {}\n        constexpr _edge(int _to, T _dist) : to(_to), dist(_dist)\
    \ {}\n        bool operator<(const _edge &rhs) const { return this->dist < rhs.dist;\
    \ }\n        bool operator>(const _edge &rhs) const { return rhs < *this; }\n\
    \    };\n    std::vector<T> dists(g.size(), inf);\n    heap<T> p_que(g.size());\n\
    \    dists[s] = T();\n    p_que.emplace(s, T());\n    while (!p_que.empty()) {\n\
    \        auto [to, dist] = p_que.top();\n        p_que.pop();\n        if (dists[to]\
    \ < dist) continue;\n        for (auto &i : g[to]) {\n            if (chmin(dists[i.to],\
    \ dist + i.dist)) p_que.emplace(i.to, dist + i.dist);\n        }\n    }\n    return\
    \ dists;\n}\n"
  dependsOn:
  - lib/graph/graph.hpp
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/graph/dijkstra_heap.hpp
  requiredBy: []
  timestamp: '2022-01-15 20:45:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/graph/dijkstra_heap.hpp
layout: document
redirect_from:
- /library/lib/graph/dijkstra_heap.hpp
- /library/lib/graph/dijkstra_heap.hpp.html
title: lib/graph/dijkstra_heap.hpp
---
