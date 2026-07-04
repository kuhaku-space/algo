// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1346
#include <iostream>
#include <string>
#include "parser/parser.hpp"

// Miscalculation: 1 桁整数と + * のみの式を、(1) 乗算優先 と
// (2) 左から順に評価 の 2 通りで計算し、Bob の答えと照合する。
// 同じ式を 2 つの ExpressionParser で評価し分ける例
// (演算子の優先順位だけを差し替える)。
using ll = long long;
using P = ExpressionParser<ll>;

int main() {
    std::string e;
    ll ans;
    std::cin >> e >> ans;

    // 乗算優先: 標準の四則 (+ が 10, * が 20)
    ll mul_first = eval_expr<ll>(e);

    // 左から順: + と * を同一優先順位・左結合にする
    P p;
    p.binary("+", 10, P::Assoc::Left, [](ll a, ll b) { return a + b; })
        .binary("*", 10, P::Assoc::Left, [](ll a, ll b) { return a * b; })
        .atom(P::integer_atom);
    ll left = p.parse(e);

    bool m = (mul_first == ans), l = (left == ans);
    std::cout << (m && l ? 'U' : m ? 'M' : l ? 'L' : 'I') << '\n';
    return 0;
}
