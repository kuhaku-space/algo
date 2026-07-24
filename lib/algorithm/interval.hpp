#pragma once
#include <algorithm>
#include <concepts>
#include <optional>
#include <utility>

namespace internal {

template <std::integral T>
bool is_include(T l1, T r1, T l2, T r2) {
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}
template <std::integral T>
bool is_include(std::pair<T, T> p, std::pair<T, T> q) {
    return is_include(p.first, p.second, q.first, q.second);
}

/// @tparam Closed true なら閉区間、false なら半開区間として境界の重なりを判定する
template <bool Closed, std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    if constexpr (Closed) return std::max(l1, l2) <= std::min(r1, r2);
    else return std::max(l1, l2) < std::min(r1, r2);
}
template <bool Closed, std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return is_intersect<Closed>(p.first, p.second, q.first, q.second);
}

template <bool Closed, std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    if (is_intersect<Closed>(l1, r1, l2, r2)) return std::pair{std::max(l1, l2), std::min(r1, r2)};
    else return std::nullopt;
}
template <bool Closed, std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return intersection<Closed>(p.first, p.second, q.first, q.second);
}

template <bool Closed, std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    if constexpr (Closed) return std::min(r1, r2) < std::max(l1, l2);
    else return std::min(r1, r2) <= std::max(l1, l2);
}
template <bool Closed, std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return is_disjoint<Closed>(p.first, p.second, q.first, q.second);
}

}  // namespace internal

/// @brief 半開区間
/// @details 区間を $[l,r)$ として扱う演算を提供する。
namespace open_interval {

/// @brief 2つの半開区間の一方が他方を包含していれば true を返す
/// @complexity $O(1)$
using internal::is_include;

/// @brief 2つの半開区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    return internal::is_intersect<false>(l1, r1, l2, r2);
}
/// @brief 2つの半開区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return internal::is_intersect<false>(p, q);
}

/// @brief 2つの半開区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    return internal::intersection<false>(l1, r1, l2, r2);
}
/// @brief 2つの半開区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return internal::intersection<false>(p, q);
}

/// @brief 2つの半開区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return internal::is_disjoint<false>(l1, r1, l2, r2);
}
/// @brief 2つの半開区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return internal::is_disjoint<false>(p, q);
}

}  // namespace open_interval

/// @brief 閉区間
/// @details 区間を $[l,r]$ として扱う演算を提供する。
namespace closed_interval {

/// @brief 2つの閉区間の一方が他方を包含していれば true を返す
/// @complexity $O(1)$
using internal::is_include;

/// @brief 2つの閉区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    return internal::is_intersect<true>(l1, r1, l2, r2);
}
/// @brief 2つの閉区間が交差していれば true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return internal::is_intersect<true>(p, q);
}

/// @brief 2つの閉区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    return internal::intersection<true>(l1, r1, l2, r2);
}
/// @brief 2つの閉区間の共通部分を返し、交差しなければ std::nullopt を返す
/// @complexity $O(1)$
template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return internal::intersection<true>(p, q);
}

/// @brief 2つの閉区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return internal::is_disjoint<true>(l1, r1, l2, r2);
}
/// @brief 2つの閉区間が交差しなければ true を返す
/// @complexity $O(1)$
template <std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return internal::is_disjoint<true>(p, q);
}

}  // namespace closed_interval
