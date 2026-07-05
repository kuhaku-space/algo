// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1155
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include "parser/parser.hpp"

// 三値論理 (0=偽, 1=不定, 2=真)。演算子は - が 2-x (否定)、* が min (論理積)、
// + が max (論理和)。BNF は
//   <formula> ::= 0|1|2|P|Q|R | -<formula> | (<formula>*<formula>) | (<formula>+<formula>)
// で、* と + は常に括弧付き。P,Q,R が式を 2 にする割り当ての個数を数える。
//
// P,Q,R は各々 0..2 の 27 通り。値型 T = array<int,27> を「27 通りの割り当てに
// おける部分式の値ベクトル」とし、全割り当てを 1 度の解析で並列評価する。
// 割り当て i では P=i/9, Q=i/3%3, R=i%3。
using Vec = std::array<int, 27>;
using P = ExpressionParser<Vec>;

int main() {
    P parser;
    parser
        .prefix("-",
                [](const Vec &x) {
                    Vec r;
                    for (int i = 0; i < 27; ++i) r[i] = 2 - x[i];
                    return r;
                })
        .binary("*", 10, P::Assoc::Left,
                [](const Vec &a, const Vec &b) {
                    Vec r;
                    for (int i = 0; i < 27; ++i) r[i] = std::min(a[i], b[i]);
                    return r;
                })
        .binary("+", 10, P::Assoc::Left,
                [](const Vec &a, const Vec &b) {
                    Vec r;
                    for (int i = 0; i < 27; ++i) r[i] = std::max(a[i], b[i]);
                    return r;
                })
        .atom([](P &p) {
            char c = p.peek();
            p.advance();
            Vec r;
            for (int i = 0; i < 27; ++i) {
                if (c == 'P') r[i] = i / 9;
                else if (c == 'Q') r[i] = i / 3 % 3;
                else if (c == 'R') r[i] = i % 3;
                else r[i] = c - '0';
            }
            return r;
        });

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ".") break;
        Vec v = parser.parse(line);
        int cnt = 0;
        for (int i = 0; i < 27; ++i) cnt += v[i] == 2;
        std::cout << cnt << '\n';
    }
}
