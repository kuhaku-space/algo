---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/icpc/stern_brocot_tree.test.cpp
    title: test/aoj/icpc/stern_brocot_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Stern-Brocot \u6728"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.10.14/x64/lib/python3.10/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: template/template.hpp:\
    \ line -1: no such header\n"
  code: "#include \"template/template.hpp\"\n\n/**\n * @brief Stern-Brocot \u6728\n\
    \ *\n */\nstruct stern_brocot_tree {\n    constexpr stern_brocot_tree() : pl(0),\
    \ ql(1), pr(1), qr(0) {}\n    constexpr stern_brocot_tree(std::uint64_t pl, std::uint64_t\
    \ ql, std::uint64_t pr,\n                                std::uint64_t qr)\n \
    \       : pl(pl), ql(ql), pr(pr), qr(qr) {}\n\n    constexpr std::pair<std::uint64_t,\
    \ std::uint64_t> get() const {\n        return std::make_pair(pl + pr, ql + qr);\n\
    \    }\n\n    constexpr stern_brocot_tree get_left() const {\n        auto [p,\
    \ q] = get();\n        return stern_brocot_tree(pl, ql, p, q);\n    }\n    constexpr\
    \ stern_brocot_tree get_right() const {\n        auto [p, q] = get();\n      \
    \  return stern_brocot_tree(p, q, pr, qr);\n    }\n\n  private:\n    std::uint64_t\
    \ pl, ql, pr, qr;\n};\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/tree/stern_brocot_tree.hpp
  requiredBy: []
  timestamp: '2023-10-01 03:35:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj/icpc/stern_brocot_tree.test.cpp
documentation_of: lib/tree/stern_brocot_tree.hpp
layout: document
redirect_from:
- /library/lib/tree/stern_brocot_tree.hpp
- /library/lib/tree/stern_brocot_tree.hpp.html
title: "Stern-Brocot \u6728"
---
