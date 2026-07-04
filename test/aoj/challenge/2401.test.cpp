// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2401
#include <bitset>
#include <iostream>
#include <stdexcept>
#include <string>
#include "parser/parser.hpp"

// Equation (恒等式): 変数 a..k (11 個)・定数 T/F・単項 -(NOT)・
// 二項 *(AND) +(OR) ->(IMP) からなる 2 式が恒等的に等しいか判定する。
// 値型を「2^11 通りの割り当てに対する真理値ベクトル」(bitset) にすると、
// 全割り当てを一度に評価でき、両辺の bitset が一致すれば恒等式。
constexpr int NVAR = 11;
constexpr int NASGN = 1 << NVAR;
using Bits = std::bitset<NASGN>;
using P = ExpressionParser<Bits>;

int main() {
    // 変数 i の真理値ベクトル: 割り当て k のビットが (k>>i)&1
    Bits var[NVAR], all_true, all_false;
    all_true.set();
    for (int k = 0; k < NASGN; ++k)
        for (int i = 0; i < NVAR; ++i)
            if ((k >> i) & 1) var[i].set(k);

    P p;
    p.prefix("-", [](const Bits &x) { return ~x; })
        .binary("->", 5, P::Assoc::Right, [](const Bits &x, const Bits &y) { return ~x | y; })
        .binary("+", 10, P::Assoc::Left, std::bit_or<Bits>())
        .binary("*", 20, P::Assoc::Left, std::bit_and<Bits>())
        .atom([&](P &q) -> Bits {
            char c = q.peek();
            q.advance();
            if (c == 'T') return all_true;
            if (c == 'F') return all_false;
            if (c >= 'a' && c <= 'k') return var[c - 'a'];
            throw std::runtime_error("unexpected atom");
        });

    std::string s;
    while (std::getline(std::cin, s)) {
        if (s == "#") break;
        if (s.empty()) continue;
        std::size_t eq = s.find('=');
        Bits lhs = p.parse(s.substr(0, eq));
        Bits rhs = p.parse(s.substr(eq + 1));
        std::cout << (lhs == rhs ? "YES" : "NO") << '\n';
    }
    return 0;
}
