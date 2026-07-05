// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1012
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include "parser/parser.hpp"

// Operations with Finite Sets: 集合 A..E と演算 u(和) i(積) d(差) s(対称差)・
// 前置 c(補集合) からなる式を評価する。全集合 U は入力で与えた集合の和。
// 値型を std::set<int> にした ExpressionParser の例。
// 二項演算子は同一優先順位・左結合、c は前置で最優先。
using Set = std::set<int>;
using P = ExpressionParser<Set>;

int main() {
    Set universe;  // U: このデータセットで定義された全集合の和
    Set sets[26];  // 集合名 A..E → sets['A'-'A'..]
    std::string name;

    P p;
    p.binary("u", 10, P::Assoc::Left,
             [](const Set &a, const Set &b) {
                 Set r = a;
                 r.insert(b.begin(), b.end());
                 return r;
             })
        .binary("i", 10, P::Assoc::Left,
                [](const Set &a, const Set &b) {
                    Set r;
                    for (int x : a)
                        if (b.count(x)) r.insert(x);
                    return r;
                })
        .binary("d", 10, P::Assoc::Left,
                [](const Set &a, const Set &b) {
                    Set r;
                    for (int x : a)
                        if (!b.count(x)) r.insert(x);
                    return r;
                })
        .binary("s", 10, P::Assoc::Left,
                [](const Set &a, const Set &b) {
                    Set r;
                    for (int x : a)
                        if (!b.count(x)) r.insert(x);
                    for (int x : b)
                        if (!a.count(x)) r.insert(x);
                    return r;
                })
        .prefix("c",
                [&universe](const Set &a) {
                    Set r;
                    for (int x : universe)
                        if (!a.count(x)) r.insert(x);
                    return r;
                })
        .atom([&sets](P &q) -> Set {
            char c = q.peek();
            if (c < 'A' || c > 'E') throw std::runtime_error("expected set name");
            q.advance();
            return sets[c - 'A'];
        });

    while (std::cin >> name) {
        if (name == "R") {
            int zero;
            std::string expr;
            std::cin >> zero >> expr;
            Set res = p.parse(expr);
            if (res.empty()) {
                std::cout << "NULL\n";
            } else {
                bool first = true;
                for (int x : res) {
                    if (!first) std::cout << ' ';
                    std::cout << x;
                    first = false;
                }
                std::cout << '\n';
            }
            // 次のデータセットに向けてリセット
            universe.clear();
            for (auto &s : sets) s.clear();
        } else {
            int cnt;
            std::cin >> cnt;
            int idx = name[0] - 'A';
            while (cnt--) {
                int x;
                std::cin >> x;
                sets[idx].insert(x);
                universe.insert(x);
            }
        }
    }
    return 0;
}
