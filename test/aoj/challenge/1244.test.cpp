// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1244
#include <cctype>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <string_view>
#include "parser/parser.hpp"

// 分子式の重さ: 原子記号 (大文字 or 大文字+小文字) の並びで、単位 (原子 or
// '(' 式 ')') の直後に乗数 (2..99) を後置できる。連接は重さの和。
// 未知の原子記号があれば UNKNOWN。括弧は atom 側で扱うため no_group()。
using ll = long long;
std::map<std::string, ll> weight;
using P = ExpressionParser<ll>;

int main() {
    std::string a;
    ll w;
    while (std::cin >> a) {
        if (a == "END_OF_FIRST_PART") break;
        std::cin >> w;
        weight[a] = w;
    }
    std::string line;
    while (std::cin >> line) {
        if (line == "0") break;
        P p;
        p.no_group()
            .concat(
                10, P::Assoc::Left, [](ll x, ll y) { return x + y; },
                [](std::string_view r) {
                    std::size_t i = 0;
                    while (i < r.size() && std::isspace(static_cast<unsigned char>(r[i]))) ++i;
                    return i < r.size() && (std::isupper(static_cast<unsigned char>(r[i])) || r[i] == '(');
                })
            .atom([](P &q) -> ll {
                // 番兵 '\0' により末尾でも cur() が安全に返るので size チェック不要。
                ll base;
                if (q.consume("(")) {
                    base = q.parse_expression(0);
                    if (!q.consume(")")) throw std::runtime_error("expected ')'");
                } else {
                    if (!std::isupper(static_cast<unsigned char>(q.cur()))) throw std::runtime_error("expected atom");
                    std::string sym(1, q.cur());
                    q.advance();
                    if (std::islower(static_cast<unsigned char>(q.cur()))) sym += q.cur(), q.advance();
                    auto it = weight.find(sym);
                    if (it == weight.end()) throw std::runtime_error("unknown atom");
                    base = it->second;
                }
                ll m = 0;
                bool has_mult = false;
                while (std::isdigit(static_cast<unsigned char>(q.cur()))) {
                    m = m * 10 + (q.cur() - '0');
                    q.advance();
                    has_mult = true;
                }
                if (has_mult) base *= m;
                return base;
            });
        try {
            std::cout << p.parse(line) << '\n';
        } catch (...) { std::cout << "UNKNOWN\n"; }
    }
    return 0;
}
