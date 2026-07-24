#pragma once
#include <cassert>
#include <cmath>
#include <cstdint>
#include <map>
#include <numeric>
#include <optional>
#include "internal/internal_math.hpp"
#include "math/modint.hpp"

namespace internal {

template <internal::modint mint>
bool has_sqrt_mod(mint x) {
    return x == 0 || x.pow(mint::mod() / 2) == 1;
}

// Adleman-Manders-Miller: mod - 1 = p^s * q (p ∤ q) の下で a の p^e 乗根を1つ求める
// (e <= s、a は p^e 乗剰余であることが前提)。Tonelli-Shanks を p^e 乗根へ一般化したもの。
template <internal::modint mint>
mint peth_root(mint a, std::int64_t p, int e) {
    const std::int64_t mod = mint::mod();
    std::int64_t q = mod - 1;
    int s = 0;
    while (q % p == 0) q /= p, ++s;
    std::int64_t pe = internal::pow_mod_constexpr(p, e, mod);  // p^e (< mod なので厳密値)
    // a^t が a の p^e 乗根の候補になるよう t = ((p^e - 1) q^{-1 mod p^e} q + 1) / p^e を選ぶ
    std::int64_t t = ((pe - 1) * internal::inv_gcd(q, pe).second % pe * q + 1) / pe;
    mint ans = a.pow(t);
    mint c(2);
    while (c.pow((mod - 1) / p) == 1) ++c;  // p 乗非剰余
    c = c.pow(q);
    // BSGS で p^{s-1} 乗根の離散対数を引き、Hensel 持ち上げで e から s まで精度を上げる
    std::int64_t pow_p_s1 = internal::pow_mod_constexpr(p, s - 1, mod - 1);
    int v = (int)std::sqrt((double)(s - e) * (double)p) + 1;
    mint mul = c.pow((std::int64_t)v * pow_p_s1 % (mod - 1));
    mint inv_mul = c.pow(pow_p_s1).inv();
    std::map<std::uint32_t, int> table;
    mint add(1);
    for (int i = 0; i <= v; ++i) {
        table[add.val()] = i;
        add *= mul;
    }
    for (int i = e; i < s; ++i) {
        mint err = ans.pow(pe).inv() * a;
        mint target = err.pow(internal::pow_mod_constexpr(p, s - 1 - i, mod - 1));
        for (int j = 0;; ++j) {
            auto it = table.find(target.val());
            if (it != table.end()) {
                std::int64_t exponent =
                    (std::int64_t)(j + v * it->second) * internal::pow_mod_constexpr(p, i - e, mod - 1) % (mod - 1);
                ans *= c.pow(exponent);
                break;
            }
            target *= inv_mul;
        }
    }
    return ans;
}

}  // namespace internal

/// @brief 素数法上で `x` の平方根を 1 つ返す
/// @return 平方根が存在しなければ `std::nullopt`
/// @complexity 法を $P$ として $O(\log^2 P)$
template <internal::modint mint>
std::optional<mint> sqrt_mod(mint x) {
    if (!internal::has_sqrt_mod(x)) return std::nullopt;
    const int p = mint::mod();
    if (x == 0 || x == 1) return x;
    if (p % 4 == 3) return x.pow(p / 4 + 1);
    int q = p - 1, s = 0;
    while (~q & 1) q >>= 1, ++s;
    mint z(1);
    while (internal::has_sqrt_mod(z)) ++z;
    mint c = z.pow(q);
    mint t = x.pow(q);
    mint r = x.pow(q / 2 + 1);
    while (t != 1) {
        int m = 0;
        mint u = t;
        while (u != 1) ++m, u *= u;
        while (s != m) {
            --s;
            if (s == m) r *= c;
            c *= c;
        }
        t *= c;
    }
    return r;
}

/// @brief K 乗根 mod P (P は素数) を1つ求める
/// @details x^K ≡ a (mod P) なる x を Adleman-Manders-Miller アルゴリズムで求める。
///          0^0 ≡ 1 の規約に従う。gcd(K, P - 1) の素因数ごとに @ref internal::peth_root
///          を適用して合成する。
/// @tparam mint static modint
/// @param a 右辺
/// @param k 指数 (0 <= k)
/// @return 条件を満たす x の1つ。解が存在しないときは std::nullopt
/// @complexity 法を $P$ として $O(\sqrt P\log^2 P)$
template <internal::modint mint>
std::optional<mint> kth_root_mod(mint a, std::int64_t k) {
    assert(k >= 0);
    const std::int64_t mod = mint::mod();
    if (k > 0 && a == 0) return mint(0);
    k %= mod - 1;
    std::int64_t g = std::gcd(k, mod - 1);
    if (a.pow((mod - 1) / g) != 1) return std::nullopt;
    a = a.pow(internal::inv_gcd(k / g, (mod - 1) / g).second);
    for (std::int64_t d = 2; d * d <= g; ++d) {
        int sz = 0;
        while (g % d == 0) g /= d, ++sz;
        if (sz > 0) a = internal::peth_root(a, d, sz);
    }
    if (g > 1) a = internal::peth_root(a, g, 1);
    return a;
}
