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
  bundledCode: "#line 1 \"lib/string/converter.hpp\"\n#include <locale>\n#include\
    \ <string>\n#include <vector>\n\nstruct string_converter {\n    char type(const\
    \ char &c) const {\n        return (std::islower(c) ? 'a' : std::isupper(c) ?\
    \ 'A' : std::isdigit(c) ? '0' : 0);\n    }\n    int convert(const char &c) {\n\
    \        if (!start) start = type(c);\n        return c - start;\n    }\n    int\
    \ convert(const char &c, const std::string &chars) { return chars.find(c); }\n\
    \    template <typename T>\n    auto convert(const T &v) {\n        std::vector<decltype(convert(v[0]))>\
    \ res;\n        res.reserve(v.size());\n        for (auto &&e : v) res.emplace_back(convert(e));\n\
    \        return res;\n    }\n    template <typename T>\n    auto convert(const\
    \ T &v, const std::string &chars) {\n        std::vector<decltype(convert(v[0],\
    \ chars))> res;\n        res.reserve(v.size());\n        for (auto &&e : v) res.emplace_back(convert(e,\
    \ chars));\n        return res;\n    }\n    int operator()(const char &v, char\
    \ s = 0) {\n        start = s;\n        return convert(v);\n    }\n    int operator()(const\
    \ char &v, const std::string &chars) { return convert(v, chars); }\n    template\
    \ <typename T>\n    auto operator()(const T &v, char s = 0) {\n        start =\
    \ s;\n        return convert(v);\n    }\n    template <typename T>\n    auto operator()(const\
    \ T &v, const std::string &chars) {\n        return convert(v, chars);\n    }\n\
    \n  private:\n    char start = 0;\n} to_int;\n"
  code: "#include <locale>\n#include <string>\n#include <vector>\n\nstruct string_converter\
    \ {\n    char type(const char &c) const {\n        return (std::islower(c) ? 'a'\
    \ : std::isupper(c) ? 'A' : std::isdigit(c) ? '0' : 0);\n    }\n    int convert(const\
    \ char &c) {\n        if (!start) start = type(c);\n        return c - start;\n\
    \    }\n    int convert(const char &c, const std::string &chars) { return chars.find(c);\
    \ }\n    template <typename T>\n    auto convert(const T &v) {\n        std::vector<decltype(convert(v[0]))>\
    \ res;\n        res.reserve(v.size());\n        for (auto &&e : v) res.emplace_back(convert(e));\n\
    \        return res;\n    }\n    template <typename T>\n    auto convert(const\
    \ T &v, const std::string &chars) {\n        std::vector<decltype(convert(v[0],\
    \ chars))> res;\n        res.reserve(v.size());\n        for (auto &&e : v) res.emplace_back(convert(e,\
    \ chars));\n        return res;\n    }\n    int operator()(const char &v, char\
    \ s = 0) {\n        start = s;\n        return convert(v);\n    }\n    int operator()(const\
    \ char &v, const std::string &chars) { return convert(v, chars); }\n    template\
    \ <typename T>\n    auto operator()(const T &v, char s = 0) {\n        start =\
    \ s;\n        return convert(v);\n    }\n    template <typename T>\n    auto operator()(const\
    \ T &v, const std::string &chars) {\n        return convert(v, chars);\n    }\n\
    \n  private:\n    char start = 0;\n} to_int;\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/string/converter.hpp
  requiredBy: []
  timestamp: '2024-02-24 06:27:09+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/converter.hpp
layout: document
redirect_from:
- /library/lib/string/converter.hpp
- /library/lib/string/converter.hpp.html
title: lib/string/converter.hpp
---
