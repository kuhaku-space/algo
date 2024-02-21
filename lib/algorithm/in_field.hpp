#include <cstdint>
#include <utility>

namespace internal {

template <int Idx>
struct in_field_impl {
    template <class Head, class... Tail>
    constexpr in_field_impl(Head &&head, Tail &&...tail)
        : limit(head), impl(std::forward<Tail>(tail)...) {}

    template <class Head, class... Tail>
    constexpr bool is_internal(Head x, Tail &&...tail) const {
        return 0 <= x && x < limit && impl.is_internal(std::forward<Tail>(tail)...);
    }

  private:
    std::int64_t limit;
    in_field_impl<Idx - 1> impl;
};

template <>
struct in_field_impl<0> {
    constexpr in_field_impl() {}

    constexpr bool is_internal() const {
        return true;
    }
};

}  // namespace internal

template <int Idx>
struct InField {
    template <class... Args, std::enable_if_t<(sizeof...(Args) == Idx)> * = nullptr>
    constexpr InField(Args &&...args) : entity(std::forward<Args>(args)...) {}

    template <class... Args>
    constexpr bool operator()(Args &&...args) const {
        return entity.is_internal(std::forward<Args>(args)...);
    }

  private:
    internal::in_field_impl<Idx> entity;
};
