// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1078
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "parser/parser.hpp"

// SAT-EN-3: 加法標準形 (DNF) の論理式が充足可能か判定する。
// 値型を「DNF = 矛盾しない部分割り当ての集合」にする。リテラルは 1 変数の項、
// & は項の直積 (整合するものだけ残す)、| は項集合の連結。項が 1 つでも残れば
// 充足可能。& と | を優先順位付き二項演算子にした ExpressionParser の例。
using Term = std::map<char, bool>;  // 変数 → 真偽 (言及しない変数は自由)
using DNF = std::vector<Term>;
using P = ExpressionParser<DNF>;

int main() {
    P p;
    p.binary("|", 10, P::Assoc::Left,
             [](const DNF &a, const DNF &b) {
                 DNF r = a;
                 r.insert(r.end(), b.begin(), b.end());
                 return r;
             })
        .binary("&", 20, P::Assoc::Left,
                [](const DNF &a, const DNF &b) {
                    DNF r;
                    for (const Term &x : a)
                        for (const Term &y : b) {
                            Term m = x;
                            bool ok = true;
                            for (auto &[k, v] : y) {
                                auto it = m.find(k);
                                if (it != m.end() && it->second != v) {
                                    ok = false;  // 同一変数に矛盾する割り当て
                                    break;
                                }
                                m[k] = v;
                            }
                            if (ok) r.push_back(std::move(m));
                        }
                    return r;
                })
        .atom([](P &q) -> DNF {
            bool neg = q.consume("~");
            char c = q.peek();
            q.advance();
            return {{{c, !neg}}};  // 1 リテラル: c は !neg でなければならない
        });

    std::string s;
    while (std::getline(std::cin, s)) {
        if (s == "#") break;
        if (s.empty()) continue;
        std::cout << (p.parse(s).empty() ? "no" : "yes") << '\n';
    }
    return 0;
}
