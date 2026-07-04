// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2255
#include <iostream>
#include <optional>
#include <string>
#include "parser/ambiguous_expr.hpp"

// 6/2(1+2): 四則演算をあらゆる評価順序で計算したとき、結果が何通りあり得るか。
// 割り算は絶対値の小さい方へ丸め (0 方向切り捨て = C++ の operator/)。
// 割る数が 0 の経路は無効 (nullopt で捨てる)。得られる値集合の要素数が答え。
using ll = long long;

int main() {
    AmbiguousExpr<ll> e;
    e.op('+', [](ll a, ll b) { return std::optional<ll>(a + b); })
        .op('-', [](ll a, ll b) { return std::optional<ll>(a - b); })
        .op('*', [](ll a, ll b) { return std::optional<ll>(a * b); })
        .op('/', [](ll a, ll b) -> std::optional<ll> {
            if (b == 0) return std::nullopt;
            return a / b;
        });

    std::string s;
    while (std::getline(std::cin, s)) {
        if (s == "#") break;
        if (s.empty()) continue;
        std::cout << e.values(s).size() << '\n';
    }
    return 0;
}
