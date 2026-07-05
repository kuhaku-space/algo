// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0264
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include "math/modint.hpp"
#include "parser/parser.hpp"

// 有限体電卓: 素数 p の有限体 GF(p) 上で四則演算式を評価する。
// 除数が p の倍数 (≡0) のときは NG。逆元は modint (フェルマーの小定理) に委ねる。
using ll = long long;
using P = ExpressionParser<modint>;

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        auto colon = line.find(':');
        ll p = std::stoll(line.substr(0, colon));
        if (p == 0) break;
        std::string exp = line.substr(colon + 1), compact;
        for (char ch : exp)
            if (!std::isspace(static_cast<unsigned char>(ch))) compact += ch;
        modint::set_mod(p);
        P parser;
        parser.atom(P::integer_atom)
            .binary("+", 10, P::Assoc::Left, std::plus<modint>())
            .binary("-", 10, P::Assoc::Left, std::minus<modint>())
            .binary("*", 20, P::Assoc::Left, std::multiplies<modint>())
            .binary("/", 20, P::Assoc::Left, [](const modint &a, const modint &b) {
                if (b.val() == 0) throw std::runtime_error("division by zero");
                return a / b;
            });
        try {
            modint v = parser.parse(compact);
            std::cout << compact << " = " << v << " (mod " << p << ")\n";
        } catch (...) { std::cout << "NG\n"; }
    }
    return 0;
}
