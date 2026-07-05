// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2570
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include "parser/parser.hpp"

using ll = long long;
constexpr ll MOD = 1000000007;

// Shipura の文法:
//   expr ::= term | expr ">>" term        (">>" は左結合, x>>y = floor(x/2^y))
//   term ::= number | "S" "<" expr ">"    (S<x> = x^2 mod 1e9+7)
// ">>" と閉じ記号 ">" が文字レベルで衝突するため、">>" の直後に項
// (数字 or 'S') が続くときだけシフトと解釈するガードを与える。
int main() {
    using P = ExpressionParser<ll>;
    P p;
    p.binary(
         ">>", 10, P::Assoc::Left, [](const ll &a, const ll &b) { return b >= 60 ? 0LL : (a >> b); },
         [](std::string_view after) {
             std::size_t i = 0;
             while (i < after.size() && std::isspace(static_cast<unsigned char>(after[i]))) ++i;
             return i < after.size() && (std::isdigit(static_cast<unsigned char>(after[i])) || after[i] == 'S');
         })
        .atom([](P &q) -> ll {
            if (std::isdigit(static_cast<unsigned char>(q.peek()))) return q.read_uint() % MOD;
            q.read_identifier();  // "S"
            if (!q.consume("<")) throw std::runtime_error("expected '<'");
            ll v = q.parse_expression(0);
            if (!q.consume(">")) throw std::runtime_error("expected '>'");
            return v * v % MOD;
        });

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "#") break;
        if (line.empty()) continue;
        std::cout << p.parse(line) << '\n';
    }
    return 0;
}
