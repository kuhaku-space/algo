// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/0264
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include "string/parser.hpp"

// 有限体電卓: 素数 p の有限体 GF(p) 上で四則演算式を評価する。
// 除数が p の倍数 (≡0) のときは NG。逆元はフェルマーの小定理で y^(p-2)。
using ll = long long;

static ll power(ll a, ll e, ll m) {
    ll r = 1;
    a %= m;
    while (e) {
        if (e & 1) r = r * a % m;
        a = a * a % m;
        e >>= 1;
    }
    return r;
}

using P = ExpressionParser<ll>;

int main() {
    std::string line;
    while (std::getline(std::cin, line)) {
        auto colon = line.find(':');
        ll p = std::stoll(line.substr(0, colon));
        if (p == 0) break;
        std::string exp = line.substr(colon + 1), compact;
        for (char ch : exp)
            if (!std::isspace(static_cast<unsigned char>(ch))) compact += ch;
        P parser;
        parser.atom([p](P &q) { return P::integer_atom(q) % p; })
            .binary("+", 10, P::Assoc::Left, [p](ll a, ll b) { return (a + b) % p; })
            .binary("-", 10, P::Assoc::Left, [p](ll a, ll b) { return ((a - b) % p + p) % p; })
            .binary("*", 20, P::Assoc::Left, [p](ll a, ll b) { return a * b % p; })
            .binary("/", 20, P::Assoc::Left, [p](ll a, ll b) -> ll {
                if (b % p == 0) throw std::runtime_error("division by zero");
                return a * power(b, p - 2, p) % p;
            });
        try {
            ll v = parser.parse(compact);
            std::cout << compact << " = " << v << " (mod " << p << ")\n";
        } catch (...) { std::cout << "NG\n"; }
    }
    return 0;
}
