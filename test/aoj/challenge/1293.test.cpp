// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1293
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>
#include "parser/parser.hpp"

// Common Polynomial: 1 変数多項式 2 つの GCM(最大公約多項式)を求める。
// 値型を有理数係数多項式にした ExpressionParser の例。連接=乗算、'^' は
// アトム内で最優先の冪、先頭の単項 - に対応。'(' は自前処理して ')^n' を許す。
using ll = long long;

// 有理数
struct Frac {
    ll n = 0, d = 1;
    Frac(ll x = 0) : n(x), d(1) {}
    Frac(ll a, ll b) : n(a), d(b) { norm(); }
    void norm() {
        if (d < 0) n = -n, d = -d;
        ll g = std::gcd(n < 0 ? -n : n, d);
        if (g) n /= g, d /= g;
    }
    Frac operator+(Frac o) const { return {n * o.d + o.n * d, d * o.d}; }
    Frac operator-(Frac o) const { return {n * o.d - o.n * d, d * o.d}; }
    Frac operator*(Frac o) const { return {n * o.n, d * o.d}; }
    Frac operator/(Frac o) const { return {n * o.d, d * o.n}; }
    bool zero() const { return n == 0; }
};

using Poly = std::vector<Frac>;  // 添字 = 次数

static void trim(Poly &p) {
    while (!p.empty() && p.back().zero()) p.pop_back();
}
static Poly add(const Poly &a, const Poly &b) {
    Poly r(std::max(a.size(), b.size()));
    for (std::size_t i = 0; i < a.size(); ++i) r[i] = r[i] + a[i];
    for (std::size_t i = 0; i < b.size(); ++i) r[i] = r[i] + b[i];
    trim(r);
    return r;
}
static Poly neg(const Poly &a) {
    Poly r = a;
    for (auto &c : r) c = Frac(0) - c;
    return r;
}
static Poly mul(const Poly &a, const Poly &b) {
    if (a.empty() || b.empty()) return {};
    Poly r(a.size() + b.size() - 1);
    for (std::size_t i = 0; i < a.size(); ++i)
        for (std::size_t j = 0; j < b.size(); ++j) r[i + j] = r[i + j] + a[i] * b[j];
    trim(r);
    return r;
}
static Poly powp(Poly a, ll e) {
    Poly r{Frac(1)};
    while (e-- > 0) r = mul(r, a);
    return r;
}
// 体上の剰余 (a mod b)
static Poly rem(Poly a, const Poly &b) {
    while (a.size() >= b.size() && !a.empty()) {
        Frac c = a.back() / b.back();
        std::size_t sh = a.size() - b.size();
        for (std::size_t i = 0; i < b.size(); ++i) a[sh + i] = a[sh + i] - c * b[i];
        trim(a);
    }
    return a;
}
static Poly gcd_poly(Poly a, Poly b) {
    trim(a), trim(b);
    while (!b.empty()) {
        Poly r = rem(a, b);
        a = b;
        b = r;
    }
    return a;
}

using P = ExpressionParser<Poly>;

int main() {
    P p;
    p.prefix("-", neg)
        .binary("+", 10, P::Assoc::Left, add)
        .binary("-", 10, P::Assoc::Left, [](const Poly &a, const Poly &b) { return add(a, neg(b)); })
        .concat(20, P::Assoc::Left, mul,
                [](std::string_view r) {
                    for (char c : r) {
                        if (std::isspace((unsigned char)c)) continue;
                        return c == 'x' || c == '(' || std::isdigit((unsigned char)c);
                    }
                    return false;
                })
        .no_group()  // '(' を自前処理して (…)^n を許す
        .atom([](P &q) -> Poly {
            Poly base;
            char c = q.peek();
            if (c == '(') {
                q.advance();
                base = q.parse_expression(0);
                if (!q.consume(")")) throw std::runtime_error("expected )");
            } else if (c == 'x') {
                q.advance();
                base = {Frac(0), Frac(1)};
            } else {
                base = {Frac(q.read_uint())};
            }
            if (q.peek() == '^') {
                q.advance();
                base = powp(base, q.read_uint());
            }
            return base;
        });

    std::string a, b;
    while (std::getline(std::cin, a)) {
        if (a == ".") break;
        std::getline(std::cin, b);
        Poly g = gcd_poly(p.parse(a), p.parse(b));

        // 整数係数の原始多項式へ正規化 (係数の gcd=1, 最高次係数を正に)
        if (g.empty()) {
            std::cout << "0\n";
            continue;
        }
        ll lcm = 1;
        for (auto &f : g) lcm = std::lcm(lcm, f.d);
        std::vector<ll> ip(g.size());
        for (std::size_t i = 0; i < g.size(); ++i) ip[i] = g[i].n * (lcm / g[i].d);
        ll cont = 0;
        for (ll v : ip) cont = std::gcd(cont, v < 0 ? -v : v);
        if (cont == 0) cont = 1;
        for (ll &v : ip) v /= cont;
        if (ip.back() < 0)
            for (ll &v : ip) v = -v;

        // 定数(=1)なら "1"
        if (ip.size() == 1) {
            std::cout << "1\n";
            continue;
        }
        std::string out;
        for (int d = (int)ip.size() - 1; d >= 0; --d) {
            ll v = ip[d];
            if (v == 0) continue;
            ll av = v < 0 ? -v : v;
            if (!out.empty()) out += (v > 0 ? "+" : "-");
            else if (v < 0) out += "-";
            if (d == 0) {
                out += std::to_string(av);
            } else {
                if (av != 1) out += std::to_string(av);
                out += (d == 1) ? "x" : "x^" + std::to_string(d);
            }
        }
        std::cout << out << '\n';
    }
    return 0;
}
