#include "template/template.hpp"

/**
 * @brief Stern-Brocot 木
 *
 */
struct stern_brocot_tree {
    constexpr stern_brocot_tree() : pl(0), ql(1), pr(1), qr(0) {}
    constexpr stern_brocot_tree(std::uint64_t pl, std::uint64_t ql, std::uint64_t pr,
                                std::uint64_t qr)
        : pl(pl), ql(ql), pr(pr), qr(qr) {}

    constexpr std::pair<std::uint64_t, std::uint64_t> get() const {
        return std::make_pair(pl + pr, ql + qr);
    }

    constexpr stern_brocot_tree get_left() const {
        auto [p, q] = get();
        return stern_brocot_tree(pl, ql, p, q);
    }
    constexpr stern_brocot_tree get_right() const {
        auto [p, q] = get();
        return stern_brocot_tree(p, q, pr, qr);
    }

  private:
    std::uint64_t pl, ql, pr, qr;
};
