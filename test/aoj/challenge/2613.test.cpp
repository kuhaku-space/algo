// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2613
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include "parser/parser.hpp"

// Unordered Operators: + - * (すべて左結合) の優先順位を自由に決めてよいとき
// 数式を最大化する。優先順位は 3 演算子への {0,1,2} 割り当てを全列挙(同値も可)し、
// 各割り当てで決まる一意な評価結果の最大を取る。
using ll = long long;
using P = ExpressionParser<ll>;

int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        if (s.empty()) continue;
        ll best = LLONG_MIN;
        for (int pa = 0; pa < 3; ++pa)
            for (int pb = 0; pb < 3; ++pb)
                for (int pc = 0; pc < 3; ++pc) {
                    P p;
                    p.atom(P::integer_atom)
                        .binary("+", pa, P::Assoc::Left, [](ll a, ll b) { return a + b; })
                        .binary("-", pb, P::Assoc::Left, [](ll a, ll b) { return a - b; })
                        .binary("*", pc, P::Assoc::Left, [](ll a, ll b) { return a * b; });
                    best = std::max(best, p.parse(s));
                }
        std::cout << best << '\n';
    }
    return 0;
}
