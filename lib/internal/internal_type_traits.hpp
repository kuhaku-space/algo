#pragma once
#include <cassert>
#include <concepts>
#include <numeric>
#include <type_traits>

namespace internal {

/// 体 (field) であることを表明する opt-in マーカー基底。
/// 四則演算（除算を含む）が閉じ、`0`/`1` を構築でき `==` で比較できる型が継承する。
/// 整数型・浮動小数点型は構文上は四則演算できても「体である」保証がないため
/// 区別したく、構文ベースの concept では弾けないのでマーカー方式を採る。
struct field_base {};

/// 体 (field) として扱える型。`field_base` を継承した型のみが満たす。
/// modint（素数 mod）や有理数を想定。
template <class T>
concept field = std::is_base_of_v<field_base, T>;

template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value || std::is_same<T, __int128>::value, std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value || std::is_same<T, unsigned __int128>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value, __uint128_t, unsigned __int128>;

template <class T>
using is_integral =
    typename std::conditional<std::is_integral<T>::value || is_signed_int128<T>::value || is_unsigned_int128<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using is_signed_int =
    typename std::conditional<(is_integral<T>::value && std::is_signed<T>::value) || is_signed_int128<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value && std::is_unsigned<T>::value) || is_unsigned_int128<T>::value,
                              std::true_type, std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value, make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value, std::make_unsigned<T>, std::common_type<T>>::type>::type;

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T>
using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal
