// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/3002
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include "parser/parser.hpp"

// Factorization: モニックな n 次多項式 (2≤n≤5) を相異なる整数根の一次式の積に
// 因数分解する。値型を多項式にした ExpressionParser で式を評価し、根は定数項の
// 約数に限られるので全探索。一次式 (x-r) を定数項 -r の昇順で出力。
// 項 = [係数] x [^指数] | 定数 をアトムで、+ - を二項演算子で扱う。
using ll = long long;
using Poly = std::vector<ll>;  // 添字 = 次数
using P = ExpressionParser<Poly>;

static Poly comb(const Poly &a, const Poly &b, int sign) {
    Poly r(std::max(a.size(), b.size()), 0);
    for (std::size_t i = 0; i < a.size(); ++i) r[i] += a[i];
    for (std::size_t i = 0; i < b.size(); ++i) r[i] += sign * b[i];
    return r;
}

int main() {
    P p;
    p.binary("+", 10, P::Assoc::Left, [](const Poly &a, const Poly &b) { return comb(a, b, 1); })
        .binary("-", 10, P::Assoc::Left, [](const Poly &a, const Poly &b) { return comb(a, b, -1); })
        .atom([](P &q) -> Poly {
            ll coef = 1;
            if (std::isdigit((unsigned char)q.peek())) coef = q.read_uint();
            int exp = 0;
            if (q.peek() == 'x') {
                q.advance();
                exp = 1;
                if (q.peek() == '^') q.advance(), exp = (int)q.read_uint();
            }
            Poly r(exp + 1, 0);
            r[exp] = coef;
            return r;
        });

    std::string s;
    while (std::getline(std::cin, s)) {
        if (s.empty()) continue;
        Poly f = p.parse(s);
        ll a0 = f[0];
        // 整数根は定数項の約数。各根 r に対し一次式 (x-r) の定数項は -r。
        std::vector<ll> consts;  // 各因子の定数項 (= -root)
        for (ll r = -std::abs(a0); r <= std::abs(a0); ++r) {
            if (r == 0 || a0 % r != 0) continue;
            __int128 v = 0;
            for (int i = (int)f.size() - 1; i >= 0; --i) v = v * r + f[i];
            if (v == 0) consts.push_back(-r);
        }
        std::sort(consts.begin(), consts.end());
        for (ll c : consts) std::cout << (c < 0 ? "(x-" + std::to_string(-c) : "(x+" + std::to_string(c)) << ')';
        std::cout << '\n';
    }
    return 0;
}
