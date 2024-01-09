---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: lib/data_structure/bigint.hpp
    title: "\u591A\u500D\u9577\u6574\u6570"
  - icon: ':warning:'
    path: lib/fft/formal_power_series.hpp
    title: lib/fft/formal_power_series.hpp
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt.hpp
    title: "\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/fft/ntt_mod.hpp
    title: "\u4EFB\u610Fmod\u7573\u307F\u8FBC\u307F"
  - icon: ':heavy_check_mark:'
    path: lib/internal/internal_fft.hpp
    title: lib/internal/internal_fft.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/combination.hpp
    title: lib/math/combination.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/enumeration.hpp
    title: lib/math/enumeration.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/modint.hpp
    title: lib/math/modint.hpp
  - icon: ':heavy_check_mark:'
    path: lib/math/sqrt.hpp
    title: lib/math/sqrt.hpp
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
    path: test/yosupo/convolution/bitwise_and_convolution.test.cpp
    title: test/yosupo/convolution/bitwise_and_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/bitwise_xor_convolution.test.cpp
    title: test/yosupo/convolution/bitwise_xor_convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution.test.cpp
    title: test/yosupo/convolution/convolution.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/convolution/convolution_mod.test.cpp
    title: test/yosupo/convolution/convolution_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/data_structure/addition_of_big_integers.test.cpp
    title: test/yosupo/data_structure/addition_of_big_integers.test.cpp
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
    path: test/yosupo/math/number_of_subsequences.test.cpp
    title: test/yosupo/math/number_of_subsequences.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/math/sqrt_mod.test.cpp
    title: test/yosupo/math/sqrt_mod.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/determinant_of_matrix.test.cpp
    title: test/yosupo/matrix/determinant_of_matrix.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/matrix/matrix_product.test.cpp
    title: test/yosupo/matrix/matrix_product.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo/tree/tree_path_composite_sum.test.cpp
    title: test/yosupo/tree/tree_path_composite_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"lib/internal/internal_type_traits.hpp\"\n#include <cassert>\n\
    #include <numeric>\n#include <type_traits>\n\nnamespace internal {\n\ntemplate\
    \ <class T>\nusing is_signed_int128 = typename std::conditional<std::is_same<T,\
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
  code: "#pragma once\n#include <cassert>\n#include <numeric>\n#include <type_traits>\n\
    \nnamespace internal {\n\ntemplate <class T>\nusing is_signed_int128 = typename\
    \ std::conditional<std::is_same<T, __int128_t>::value ||\n                   \
    \                                    std::is_same<T, __int128>::value,\n     \
    \                                              std::true_type, std::false_type>::type;\n\
    \ntemplate <class T>\nusing is_unsigned_int128 = typename std::conditional<std::is_same<T,\
    \ __uint128_t>::value ||\n                                                   \
    \      std::is_same<T, unsigned __int128>::value,\n                          \
    \                           std::true_type, std::false_type>::type;\n\ntemplate\
    \ <class T>\nusing make_unsigned_int128 =\n    typename std::conditional<std::is_same<T,\
    \ __int128_t>::value, __uint128_t, unsigned __int128>;\n\ntemplate <class T>\n\
    using is_integral =\n    typename std::conditional<std::is_integral<T>::value\
    \ || is_signed_int128<T>::value ||\n                                  is_unsigned_int128<T>::value,\n\
    \                              std::true_type, std::false_type>::type;\n\ntemplate\
    \ <class T>\nusing is_signed_int =\n    typename std::conditional<(is_integral<T>::value\
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
  dependsOn: []
  isVerificationFile: false
  path: lib/internal/internal_type_traits.hpp
  requiredBy:
  - lib/fft/ntt.hpp
  - lib/fft/ntt_mod.hpp
  - lib/fft/formal_power_series.hpp
  - lib/math/modint.hpp
  - lib/math/enumeration.hpp
  - lib/math/sqrt.hpp
  - lib/math/combination.hpp
  - lib/data_structure/bigint.hpp
  - lib/internal/internal_fft.hpp
  timestamp: '2023-10-01 18:31:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo/matrix/determinant_of_matrix.test.cpp
  - test/yosupo/matrix/matrix_product.test.cpp
  - test/yosupo/math/sqrt_mod.test.cpp
  - test/yosupo/math/number_of_subsequences.test.cpp
  - test/yosupo/convolution/convolution_mod.test.cpp
  - test/yosupo/convolution/convolution.test.cpp
  - test/yosupo/convolution/bitwise_xor_convolution.test.cpp
  - test/yosupo/convolution/bitwise_and_convolution.test.cpp
  - test/yosupo/data_structure/point_set_range_composite.test.cpp
  - test/yosupo/data_structure/queue_operate_all_composite.test.cpp
  - test/yosupo/data_structure/range_affine_range_sum.test.cpp
  - test/yosupo/data_structure/vertex_set_path_composite.test.cpp
  - test/yosupo/data_structure/addition_of_big_integers.test.cpp
  - test/yosupo/tree/tree_path_composite_sum.test.cpp
  - test/aoj/dpl/stirling.test.cpp
  - test/aoj/dpl/bell.test.cpp
  - test/aoj/jag/aho_corasick.test.cpp
  - test/aoj/ntl/multiplication.test.cpp
  - test/aoj/ntl/remainder.test.cpp
  - test/aoj/ntl/division.test.cpp
  - test/aoj/ntl/difference.test.cpp
  - test/aoj/ntl/multiplication2.test.cpp
  - test/aoj/ntl/power.test.cpp
  - test/aoj/ntl/addition.test.cpp
documentation_of: lib/internal/internal_type_traits.hpp
layout: document
redirect_from:
- /library/lib/internal/internal_type_traits.hpp
- /library/lib/internal/internal_type_traits.hpp.html
title: lib/internal/internal_type_traits.hpp
---
