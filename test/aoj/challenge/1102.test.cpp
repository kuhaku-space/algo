// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1102
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include "parser/parser.hpp"

// 複素数式の評価: + - * (二項のみ) と括弧、非負整数と虚数単位 i。
// 途中結果を含め実部・虚部の絶対値が 10000 を超えたら overflow。
// 値型 T をユーザ定義の複素数型にした ExpressionParser<C> の例。
using ll = long long;

struct C {
    ll re = 0, im = 0;
};

static const ll LIM = 10000;
static C chk(C x) {
    if (x.re > LIM || x.re < -LIM || x.im > LIM || x.im < -LIM) throw std::runtime_error("overflow");
    return x;
}

using P = ExpressionParser<C>;

int main() {
    std::string s;
    while (std::getline(std::cin, s)) {
        if (s.empty()) continue;
        P p;
        p.binary("+", 10, P::Assoc::Left, [](C a, C b) { return chk({a.re + b.re, a.im + b.im}); })
            .binary("-", 10, P::Assoc::Left, [](C a, C b) { return chk({a.re - b.re, a.im - b.im}); })
            .binary("*", 20, P::Assoc::Left,
                    [](C a, C b) { return chk({a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re}); })
            .atom([](P &q) -> C {
                if (q.peek() == 'i') {
                    q.advance();
                    return {0, 1};
                }
                std::string_view r = q.rest();
                std::size_t k = 0;
                ll v = 0;
                while (k < r.size() && std::isdigit(static_cast<unsigned char>(r[k]))) {
                    v = v * 10 + (r[k] - '0');
                    if (v > 1000000000) v = 1000000000;
                    ++k;
                }
                if (k == 0) throw std::runtime_error("expected number or i");
                q.advance(k);
                return chk({v, 0});
            });
        try {
            C r = p.parse(s);
            std::string out;
            if (r.im == 0) out = std::to_string(r.re);
            else if (r.re == 0) out = std::to_string(r.im) + "i";
            else out = std::to_string(r.re) + (r.im > 0 ? "+" : "") + std::to_string(r.im) + "i";
            std::cout << out << '\n';
        } catch (...) { std::cout << "overflow\n"; }
    }
    return 0;
}
