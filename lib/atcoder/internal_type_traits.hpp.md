---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: lib/atcoder/convolution.hpp
    title: lib/atcoder/convolution.hpp
  - icon: ':warning:'
    path: lib/atcoder/fenwicktree.hpp
    title: lib/atcoder/fenwicktree.hpp
  - icon: ':warning:'
    path: lib/atcoder/modint.hpp
    title: lib/atcoder/modint.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/atcoder/internal_type_traits.hpp\"\n\n\n\r\n#include\
    \ <cassert>\r\n#include <numeric>\r\n#include <type_traits>\r\n\r\nnamespace atcoder\
    \ {\r\n\r\nnamespace internal {\r\n\r\n#ifndef _MSC_VER\r\ntemplate <class T>\r\
    \nusing is_signed_int128 =\r\n    typename std::conditional<std::is_same<T, __int128_t>::value\
    \ ||\r\n                                  std::is_same<T, __int128>::value,\r\n\
    \                              std::true_type,\r\n                           \
    \   std::false_type>::type;\r\n\r\ntemplate <class T>\r\nusing is_unsigned_int128\
    \ =\r\n    typename std::conditional<std::is_same<T, __uint128_t>::value ||\r\n\
    \                                  std::is_same<T, unsigned __int128>::value,\r\
    \n                              std::true_type,\r\n                          \
    \    std::false_type>::type;\r\n\r\ntemplate <class T>\r\nusing make_unsigned_int128\
    \ =\r\n    typename std::conditional<std::is_same<T, __int128_t>::value,\r\n \
    \                             __uint128_t,\r\n                              unsigned\
    \ __int128>;\r\n\r\ntemplate <class T>\r\nusing is_integral = typename std::conditional<std::is_integral<T>::value\
    \ ||\r\n                                                  is_signed_int128<T>::value\
    \ ||\r\n                                                  is_unsigned_int128<T>::value,\r\
    \n                                              std::true_type,\r\n          \
    \                                    std::false_type>::type;\r\n\r\ntemplate <class\
    \ T>\r\nusing is_signed_int = typename std::conditional<(is_integral<T>::value\
    \ &&\r\n                                                 std::is_signed<T>::value)\
    \ ||\r\n                                                    is_signed_int128<T>::value,\r\
    \n                                                std::true_type,\r\n        \
    \                                        std::false_type>::type;\r\n\r\ntemplate\
    \ <class T>\r\nusing is_unsigned_int =\r\n    typename std::conditional<(is_integral<T>::value\
    \ &&\r\n                               std::is_unsigned<T>::value) ||\r\n    \
    \                              is_unsigned_int128<T>::value,\r\n             \
    \                 std::true_type,\r\n                              std::false_type>::type;\r\
    \n\r\ntemplate <class T>\r\nusing to_unsigned = typename std::conditional<\r\n\
    \    is_signed_int128<T>::value,\r\n    make_unsigned_int128<T>,\r\n    typename\
    \ std::conditional<std::is_signed<T>::value,\r\n                             \
    \ std::make_unsigned<T>,\r\n                              std::common_type<T>>::type>::type;\r\
    \n\r\n#else\r\n\r\ntemplate <class T> using is_integral = typename std::is_integral<T>;\r\
    \n\r\ntemplate <class T>\r\nusing is_signed_int =\r\n    typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\r\n                              std::true_type,\r\
    \n                              std::false_type>::type;\r\n\r\ntemplate <class\
    \ T>\r\nusing is_unsigned_int =\r\n    typename std::conditional<is_integral<T>::value\
    \ &&\r\n                                  std::is_unsigned<T>::value,\r\n    \
    \                          std::true_type,\r\n                              std::false_type>::type;\r\
    \n\r\ntemplate <class T>\r\nusing to_unsigned = typename std::conditional<is_signed_int<T>::value,\r\
    \n                                              std::make_unsigned<T>,\r\n   \
    \                                           std::common_type<T>>::type;\r\n\r\n\
    #endif\r\n\r\ntemplate <class T>\r\nusing is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\r\
    \n\r\ntemplate <class T>\r\nusing is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\r\
    \n\r\ntemplate <class T> using to_unsigned_t = typename to_unsigned<T>::type;\r\
    \n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n\n"
  code: "#ifndef ATCODER_INTERNAL_TYPE_TRAITS_HPP\r\n#define ATCODER_INTERNAL_TYPE_TRAITS_HPP\
    \ 1\r\n\r\n#include <cassert>\r\n#include <numeric>\r\n#include <type_traits>\r\
    \n\r\nnamespace atcoder {\r\n\r\nnamespace internal {\r\n\r\n#ifndef _MSC_VER\r\
    \ntemplate <class T>\r\nusing is_signed_int128 =\r\n    typename std::conditional<std::is_same<T,\
    \ __int128_t>::value ||\r\n                                  std::is_same<T, __int128>::value,\r\
    \n                              std::true_type,\r\n                          \
    \    std::false_type>::type;\r\n\r\ntemplate <class T>\r\nusing is_unsigned_int128\
    \ =\r\n    typename std::conditional<std::is_same<T, __uint128_t>::value ||\r\n\
    \                                  std::is_same<T, unsigned __int128>::value,\r\
    \n                              std::true_type,\r\n                          \
    \    std::false_type>::type;\r\n\r\ntemplate <class T>\r\nusing make_unsigned_int128\
    \ =\r\n    typename std::conditional<std::is_same<T, __int128_t>::value,\r\n \
    \                             __uint128_t,\r\n                              unsigned\
    \ __int128>;\r\n\r\ntemplate <class T>\r\nusing is_integral = typename std::conditional<std::is_integral<T>::value\
    \ ||\r\n                                                  is_signed_int128<T>::value\
    \ ||\r\n                                                  is_unsigned_int128<T>::value,\r\
    \n                                              std::true_type,\r\n          \
    \                                    std::false_type>::type;\r\n\r\ntemplate <class\
    \ T>\r\nusing is_signed_int = typename std::conditional<(is_integral<T>::value\
    \ &&\r\n                                                 std::is_signed<T>::value)\
    \ ||\r\n                                                    is_signed_int128<T>::value,\r\
    \n                                                std::true_type,\r\n        \
    \                                        std::false_type>::type;\r\n\r\ntemplate\
    \ <class T>\r\nusing is_unsigned_int =\r\n    typename std::conditional<(is_integral<T>::value\
    \ &&\r\n                               std::is_unsigned<T>::value) ||\r\n    \
    \                              is_unsigned_int128<T>::value,\r\n             \
    \                 std::true_type,\r\n                              std::false_type>::type;\r\
    \n\r\ntemplate <class T>\r\nusing to_unsigned = typename std::conditional<\r\n\
    \    is_signed_int128<T>::value,\r\n    make_unsigned_int128<T>,\r\n    typename\
    \ std::conditional<std::is_signed<T>::value,\r\n                             \
    \ std::make_unsigned<T>,\r\n                              std::common_type<T>>::type>::type;\r\
    \n\r\n#else\r\n\r\ntemplate <class T> using is_integral = typename std::is_integral<T>;\r\
    \n\r\ntemplate <class T>\r\nusing is_signed_int =\r\n    typename std::conditional<is_integral<T>::value\
    \ && std::is_signed<T>::value,\r\n                              std::true_type,\r\
    \n                              std::false_type>::type;\r\n\r\ntemplate <class\
    \ T>\r\nusing is_unsigned_int =\r\n    typename std::conditional<is_integral<T>::value\
    \ &&\r\n                                  std::is_unsigned<T>::value,\r\n    \
    \                          std::true_type,\r\n                              std::false_type>::type;\r\
    \n\r\ntemplate <class T>\r\nusing to_unsigned = typename std::conditional<is_signed_int<T>::value,\r\
    \n                                              std::make_unsigned<T>,\r\n   \
    \                                           std::common_type<T>>::type;\r\n\r\n\
    #endif\r\n\r\ntemplate <class T>\r\nusing is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\r\
    \n\r\ntemplate <class T>\r\nusing is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\r\
    \n\r\ntemplate <class T> using to_unsigned_t = typename to_unsigned<T>::type;\r\
    \n\r\n}  // namespace internal\r\n\r\n}  // namespace atcoder\r\n\r\n#endif  //\
    \ ATCODER_INTERNAL_TYPE_TRAITS_HPP\r\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/atcoder/internal_type_traits.hpp
  requiredBy:
  - lib/atcoder/modint.hpp
  - lib/atcoder/convolution.hpp
  - lib/atcoder/fenwicktree.hpp
  timestamp: '2021-09-18 16:27:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/atcoder/internal_type_traits.hpp
layout: document
redirect_from:
- /library/lib/atcoder/internal_type_traits.hpp
- /library/lib/atcoder/internal_type_traits.hpp.html
title: lib/atcoder/internal_type_traits.hpp
---
