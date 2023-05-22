---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/template/template.hpp
    title: lib/template/template.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: lib/fft/ntt.hpp
  - icon: ':warning:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u6570\u8AD6\u5909\u63DB"
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/bell.test.cpp
    title: test/aoj/dpl/bell.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/dpl/stirling.test.cpp
    title: test/aoj/dpl/stirling.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/jag/aho_corasick.test.cpp
    title: test/aoj/jag/aho_corasick.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/addition.test.cpp
    title: test/aoj/ntl/addition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/difference.test.cpp
    title: test/aoj/ntl/difference.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/division.test.cpp
    title: test/aoj/ntl/division.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication.test.cpp
    title: test/aoj/ntl/multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/multiplication2.test.cpp
    title: test/aoj/ntl/multiplication2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/power.test.cpp
    title: test/aoj/ntl/power.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj/ntl/remainder.test.cpp
    title: test/aoj/ntl/remainder.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution.test.cpp
    title: test/yosupo/convolution/convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/point_set_range_composite.test.cpp
    title: test/yosupo/data_structure/point_set_range_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
    title: test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/range_affine_range_sum.test.cpp
    title: test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
    title: test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/matrix_product.test.cpp
    title: test/yosupo/matrix/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/new/number_of_subsequences.test.cpp
    title: test/yosupo/new/number_of_subsequences.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/tree_path_composite_sum.test.cpp
    title: test/yosupo/tree/tree_path_composite_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
  code: "#pragma once\n#include \"template/template.hpp\"\n\nnamespace internal {\n\
    \ntemplate <class T>\nusing is_signed_int128 = typename std::conditional<std::is_same<T,\
    \ __int128_t>::value ||\n                                                    \
    \   std::is_same<T, __int128>::value,\n                                      \
    \             std::true_type, std::false_type>::type;\n\ntemplate <class T>\n\
    using is_unsigned_int128 = typename std::conditional<std::is_same<T, __uint128_t>::value\
    \ ||\n                                                         std::is_same<T,\
    \ unsigned __int128>::value,\n                                               \
    \      std::true_type, std::false_type>::type;\n\ntemplate <class T>\nusing make_unsigned_int128\
    \ =\n    typename std::conditional<std::is_same<T, __int128_t>::value, __uint128_t,\
    \ unsigned __int128>;\n\ntemplate <class T>\nusing is_integral =\n    typename\
    \ std::conditional<std::is_integral<T>::value || is_signed_int128<T>::value ||\n\
    \                                  is_unsigned_int128<T>::value,\n           \
    \                   std::true_type, std::false_type>::type;\n\ntemplate <class\
    \ T>\nusing is_signed_int =\n    typename std::conditional<(is_integral<T>::value\
    \ && std::is_signed<T>::value) ||\n                                  is_signed_int128<T>::value,\n\
    \                              std::true_type, std::false_type>::type;\n\ntemplate\
    \ <class T>\nusing is_unsigned_int =\n    typename std::conditional<(is_integral<T>::value\
    \ && std::is_unsigned<T>::value) ||\n                                  is_unsigned_int128<T>::value,\n\
    \                              std::true_type, std::false_type>::type;\n\ntemplate\
    \ <class T>\nusing to_unsigned = typename std::conditional<\n    is_signed_int128<T>::value,\
    \ make_unsigned_int128<T>,\n    typename std::conditional<std::is_signed<T>::value,\
    \ std::make_unsigned<T>,\n                              std::common_type<T>>::type>::type;\n\
    \ntemplate <class T>\nusing is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \ntemplate <class T>\nusing is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \ntemplate <class T>\nusing to_unsigned_t = typename to_unsigned<T>::type;\n\n\
    }  // namespace internal\n"
  dependsOn:
  - lib/template/template.hpp
  isVerificationFile: false
  path: lib/internal/internal_type_traits.hpp
  requiredBy:
  - lib/data_structure/bigint.hpp
  - lib/fft/ntt.hpp
  - lib/fft/formal_power_series.hpp
  - lib/fft/ntt_mod.hpp
  - lib/math/combination.hpp
  - lib/math/enumeration.hpp
  - lib/math/modint.hpp
  timestamp: '2023-05-22 19:46:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/new/number_of_subsequences.test.cpp
  - test/yosupo/tree/tree_path_composite_sum.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - test/yosupo/matrix/matrix_product.test.cpp
  - test/aoj/jag/aho_corasick.test.cpp
  - test/aoj/dpl/bell.test.cpp
  - test/aoj/dpl/stirling.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/power.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/addition.test.cpp
documentation_of: lib/internal/internal_type_traits.hpp
layout: document
redirect_from:
- /library/lib/internal/internal_type_traits.hpp
- /library/lib/internal/internal_type_traits.hpp.html
title: lib/internal/internal_type_traits.hpp
---
