#pragma once
#include <cstdint>
#include <utility>

namespace internal {

template <int Index>
struct grid_impl {
    template <class Head, class... Tail>
    constexpr grid_impl(Head &&head, Tail &&...tail) : limit(head), impl(std::forward<Tail>(tail)...) {}

    template <class Head, class... Tail>
    constexpr bool in_field(Head x, Tail &&...tail) const {
        return 0 <= x && x < limit && impl.in_field(std::forward<Tail>(tail)...);
    }

    template <class Head, class... Tail>
    constexpr std::int64_t flatten(Head x, Tail &&...tail) const {
        return x + limit * impl.flatten(std::forward<Tail>(tail)...);
    }

  private:
    std::int64_t limit;
    grid_impl<Index - 1> impl;
};

template <>
struct grid_impl<0> {
    constexpr grid_impl() {}

    constexpr bool in_field() const { return true; }

    constexpr std::int64_t flatten() const { return 0; }
};

}  // namespace internal

template <int Index>
struct Grid {
    template <class... Args>
    constexpr Grid(Args &&...args) : entity(std::forward<Args>(args)...) {
        static_assert(sizeof...(Args) == Index);
    }

    template <class... Args>
    constexpr bool in_field(Args &&...args) const {
        static_assert(sizeof...(Args) == Index);
        return entity.in_field(std::forward<Args>(args)...);
    }

    template <class... Args>
    constexpr std::int64_t flatten(Args &&...args) const {
        static_assert(sizeof...(Args) == Index);
        return entity.flatten(std::forward<Args>(args)...);
    }

  private:
    internal::grid_impl<Index> entity;
};
