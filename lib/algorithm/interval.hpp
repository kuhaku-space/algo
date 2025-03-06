#pragma once
#include <algorithm>
#include <concepts>
#include <optional>
#include <utility>

/// @brief 半開区間
namespace open_interval {

template <std::integral T>
bool is_include(T l1, T r1, T l2, T r2) {
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}

template <std::integral T>
bool is_include(std::pair<T, T> p, std::pair<T, T> q) {
    return is_include(p.first, p.second, q.first, q.second);
}

template <std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    return std::max(l1, l2) < std::min(r1, r2);
}

template <std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return is_intersect(p.first, p.second, q.first, q.second);
}

template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    if (is_intersect(l1, r1, l2, r2)) return {std::max(l1, l2), std::min(r1, r2)};
    else return std::nullopt;
}

template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return intersection(p.first, p.second, q.first, q.second);
}

template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return std::min(r1, r2) <= std::max(l1, l2);
}

template <std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return is_disjoint(p.first, p.second, q.first, q.second);
}

}  // namespace open_interval

/// @brief 閉区間
namespace closed_interval {

template <std::integral T>
bool is_include(T l1, T r1, T l2, T r2) {
    return (l1 <= l2 && r2 <= r1) || (l2 <= l1 && r1 <= r2);
}

template <std::integral T>
bool is_include(std::pair<T, T> p, std::pair<T, T> q) {
    return is_include(p.first, p.second, q.first, q.second);
}

template <std::integral T>
bool is_intersect(T l1, T r1, T l2, T r2) {
    return std::max(l1, l2) <= std::min(r1, r2);
}

template <std::integral T>
bool is_intersect(std::pair<T, T> p, std::pair<T, T> q) {
    return is_intersect(p.first, p.second, q.first, q.second);
}

template <std::integral T>
std::optional<std::pair<T, T>> intersection(T l1, T r1, T l2, T r2) {
    if (is_intersect(l1, r1, l2, r2)) return {std::max(l1, l2), std::min(r1, r2)};
    else return std::nullopt;
}

template <std::integral T>
std::optional<std::pair<T, T>> intersection(std::pair<T, T> p, std::pair<T, T> q) {
    return intersection(p.first, p.second, q.first, q.second);
}

template <std::integral T>
bool is_disjoint(T l1, T r1, T l2, T r2) {
    return std::min(r1, r2) < std::max(l1, l2);
}

template <std::integral T>
bool is_disjoint(std::pair<T, T> p, std::pair<T, T> q) {
    return is_disjoint(p.first, p.second, q.first, q.second);
}

}  // namespace closed_interval
