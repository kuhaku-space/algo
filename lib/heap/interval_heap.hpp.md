---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/alds1/interval_heap.test.cpp
    title: test/aoj/alds1/interval_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Interval Heap
    links:
    - https://scrapbox.io/data-structures/Interval_Heap
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.13/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief Interval Heap\n *\n\
    \ * @tparam T\n *\n * @see https://scrapbox.io/data-structures/Interval_Heap\n\
    \ */\ntemplate <class T>\nstruct interval_heap {\n    constexpr interval_heap()\
    \ : _size(), data(1) {}\n\n    constexpr int empty() const { return _size == 0;\
    \ }\n    constexpr int size() const { return _size; }\n\n    T get_max() const\
    \ {\n        assert(_size);\n        return data[1];\n    }\n    T get_min() const\
    \ {\n        assert(_size);\n        return _size == 1 ? data[1] : data[2];\n\
    \    }\n\n    void push(const T &x) {\n        data.push_back(x);\n        apply();\n\
    \    }\n    void push(T &&x) {\n        data.push_back(std::move(x));\n      \
    \  apply();\n    }\n    template <typename... Args>\n    void emplace(Args &&...args)\
    \ {\n        data.emplace_back(std::forward<Args>(args)...);\n        apply();\n\
    \    }\n\n    void pop_max() {\n        assert(_size);\n        --_size;\n   \
    \     if (_size < 2) {\n            if (_size == 1) std::swap(data[1], data[2]);\n\
    \            data.pop_back();\n        } else {\n            std::swap(data[1],\
    \ data.back());\n            data.pop_back();\n            down(1);\n        }\n\
    \    }\n\n    void pop_min() {\n        assert(_size);\n        --_size;\n   \
    \     if (_size < 2) {\n            data.pop_back();\n        } else {\n     \
    \       std::swap(data[2], data.back());\n            data.pop_back();\n     \
    \       up(2);\n        }\n    }\n\n  private:\n    int _size;\n    std::vector<T>\
    \ data;\n\n    std::pair<int, int> next(int idx) {\n        assert(idx != 2 &&\
    \ _size >= 2);\n        if (idx & 1) {\n            if (idx * 2 + 1 <= _size)\
    \ {\n                idx = idx * 2 + 1;\n                return std::make_pair(idx,\
    \ idx + 2 <= _size ? idx + 2 : idx);\n            }\n            ++idx;\n    \
    \        if (idx <= _size) return std::make_pair(idx, idx);\n        }\n     \
    \   idx = (idx / 2) & ~1;\n        return std::make_pair(idx, idx);\n    }\n\n\
    \    std::pair<int, int> prev(int idx) {\n        assert(idx != 1);\n        if\
    \ (~idx & 1) {\n            if (idx * 2 - 1 <= _size) {\n                idx =\
    \ idx * 2;\n                if (idx + 2 <= _size) return std::make_pair(idx, idx\
    \ + 2);\n                if (idx <= _size) return std::make_pair(idx, idx);\n\
    \            }\n            --idx;\n            return std::make_pair(idx, idx);\n\
    \        }\n        idx = (idx / 2 - 1) | 1;\n        return std::make_pair(idx,\
    \ idx);\n    }\n\n    int down(int idx) {\n        while (idx != 2) {\n      \
    \      auto &&[x, y] = next(idx);\n            if (x != y && data[x] < data[y])\
    \ std::swap(x, y);\n            if (data[x] < data[idx]) break;\n            std::swap(data[x],\
    \ data[idx]);\n            idx = x;\n        }\n        return idx;\n    }\n\n\
    \    int up(int idx) {\n        while (idx != 1) {\n            auto &&[x, y]\
    \ = prev(idx);\n            if (x != y && data[y] < data[x]) std::swap(x, y);\n\
    \            if (data[idx] < data[x]) break;\n            std::swap(data[idx],\
    \ data[x]);\n            idx = x;\n        }\n        return idx;\n    }\n\n \
    \   void apply() {\n        ++_size;\n        if (_size >= 3) {\n            int\
    \ idx = _size;\n            idx = down(idx);\n            idx = up(idx);\n   \
    \     } else if (_size == 2 && data[1] < data[2]) {\n            std::swap(data[1],\
    \ data[2]);\n        }\n    }\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/heap/interval_heap.hpp
  requiredBy: []
  timestamp: '2023-09-28 01:09:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/alds1/interval_heap.test.cpp
documentation_of: lib/heap/interval_heap.hpp
layout: document
redirect_from:
- /library/lib/heap/interval_heap.hpp
- /library/lib/heap/interval_heap.hpp.html
title: Interval Heap
---
