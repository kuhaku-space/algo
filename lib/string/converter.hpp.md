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
  code: "#include \"template/template.hpp\"\n\nstruct string_converter {\n    char\
    \ type(const char &c) const {\n        return (std::islower(c) ? 'a' : std::isupper(c)\
    \ ? 'A' : std::isdigit(c) ? '0' : 0);\n    }\n    int convert(const char &c) {\n\
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
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/string/converter.hpp
  requiredBy: []
  timestamp: '2023-02-11 17:20:29+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/string/converter.hpp
layout: document
redirect_from:
- /library/lib/string/converter.hpp
- /library/lib/string/converter.hpp.html
title: lib/string/converter.hpp
---
