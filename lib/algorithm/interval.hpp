#pragma once
#include <algorithm>
#include <concepts>
#include <optional>
#include <utility>

/// @file
/// @brief 区間演算
/// @details 半開区間 $[l, r)$ と閉区間 $[l, r]$ の包含・交差判定と共通部分を提供する。

namespace internal {

namespace interval {

template <std::integral T>
bool is_nested(T l1, T r1, T l2, T r2) {
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}

/// @tparam Closed true なら閉区間、false なら半開区間として境界の重なりを判定する
template <bool Closed, std::integral T>
bool is_intersecting(T l1, T r1, T l2, T r2) {
    if constexpr (Closed) return std::max(l1, l2) <= std::min(r1, r2);
    else return std::max(l1, l2) < std::min(r1, r2);
}

/// @tparam Closed true なら閉区間、false なら半開区間として境界の重なりを判定する
template <bool Closed, std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    if (is_intersecting<Closed>(l1, r1, l2, r2)) return std::pair{std::max(l1, l2), std::min(r1, r2)};
    else return std::nullopt;
}

/// @tparam Closed true なら閉区間、false なら半開区間として境界の重なりを判定する
template <bool Closed, std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    if constexpr (Closed) return std::min(r1, r2) < std::max(l1, l2);
    else return std::min(r1, r2) <= std::max(l1, l2);
}

}  // namespace interval

}  // namespace internal

/// @brief 半開区間
/// @details 区間を $[l, r)$ として扱う演算を提供する。
namespace half_open_interval {

/// @brief 2つの半開区間が入れ子（一方が他方を包含する）であれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_nested(T l1, T r1, T l2, T r2) {
    return internal::interval::is_nested(l1, r1, l2, r2);
}
/// @brief 2つの半開区間が入れ子（一方が他方を包含する）であれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_nested(std::pair<T, T> a, std::pair<T, T> b) {
    return is_nested(a.first, a.second, b.first, b.second);
}

/// @brief 2つの半開区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersecting(T l1, T r1, T l2, T r2) {
    return internal::interval::is_intersecting<false>(l1, r1, l2, r2);
}
/// @brief 2つの半開区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersecting(std::pair<T, T> a, std::pair<T, T> b) {
    return is_intersecting(a.first, a.second, b.first, b.second);
}

/// @brief 2つの半開区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    return internal::interval::intersection<false>(l1, r1, l2, r2);
}
/// @brief 2つの半開区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> a, std::pair<T, T> b) {
    return intersection(a.first, a.second, b.first, b.second);
}

/// @brief 2つの半開区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return internal::interval::is_disjoint<false>(l1, r1, l2, r2);
}
/// @brief 2つの半開区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(std::pair<T, T> a, std::pair<T, T> b) {
    return is_disjoint(a.first, a.second, b.first, b.second);
}

}  // namespace half_open_interval

/// @brief 閉区間
/// @details 区間を $[l, r]$ として扱う演算を提供する。
namespace closed_interval {

/// @brief 2つの閉区間が入れ子（一方が他方を包含する）であれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_nested(T l1, T r1, T l2, T r2) {
    return internal::interval::is_nested(l1, r1, l2, r2);
}
/// @brief 2つの閉区間が入れ子（一方が他方を包含する）であれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_nested(std::pair<T, T> a, std::pair<T, T> b) {
    return is_nested(a.first, a.second, b.first, b.second);
}

/// @brief 2つの閉区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersecting(T l1, T r1, T l2, T r2) {
    return internal::interval::is_intersecting<true>(l1, r1, l2, r2);
}
/// @brief 2つの閉区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersecting(std::pair<T, T> a, std::pair<T, T> b) {
    return is_intersecting(a.first, a.second, b.first, b.second);
}

/// @brief 2つの閉区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    return internal::interval::intersection<true>(l1, r1, l2, r2);
}
/// @brief 2つの閉区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> a, std::pair<T, T> b) {
    return intersection(a.first, a.second, b.first, b.second);
}

/// @brief 2つの閉区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return internal::interval::is_disjoint<true>(l1, r1, l2, r2);
}
/// @brief 2つの閉区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(std::pair<T, T> a, std::pair<T, T> b) {
    return is_disjoint(a.first, a.second, b.first, b.second);
}

}  // namespace closed_interval
