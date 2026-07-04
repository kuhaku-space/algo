// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1233
#include <array>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include "parser/parser.hpp"

// Equals are Equals: 変数 a..z の多変数多項式が等価かを判定する。
// Schwartz-Zippel: 大きな素数体 F_p 上の K 個のランダムな点で両式を評価し、
// すべて一致すれば等価とみなす。K レーンをまとめた値型で 1 回の parse で
// K 点同時評価する ExpressionParser の例。
//   expr    ::= term (('+'|'-') term)*
//   term    ::= factor+                 (連接 = 乗算)
//   factor  ::= number | var ['^' digit] | '(' expr ')'
using ull = std::uint64_t;
constexpr ull MOD = (1ULL << 61) - 1;  // メルセンヌ素数
constexpr int K = 32;                  // 評価点の数 (レーン)

static ull mul_mod(ull a, ull b) {
    __uint128_t c = (__uint128_t)a * b;
    ull lo = (ull)(c & MOD), hi = (ull)(c >> 61);
    ull r = lo + hi;
    return r >= MOD ? r - MOD : r;
}

// K 点分の体の元をまとめて持つベクトル値
struct V {
    std::array<ull, K> a{};
    V operator+(const V &o) const {
        V r;
        for (int i = 0; i < K; ++i) {
            ull s = a[i] + o.a[i];
            r.a[i] = s >= MOD ? s - MOD : s;
        }
        return r;
    }
    V operator-(const V &o) const {
        V r;
        for (int i = 0; i < K; ++i) {
            ull s = a[i] + MOD - o.a[i];
            r.a[i] = s >= MOD ? s - MOD : s;
        }
        return r;
    }
    V operator*(const V &o) const {
        V r;
        for (int i = 0; i < K; ++i) r.a[i] = mul_mod(a[i], o.a[i]);
        return r;
    }
    bool operator==(const V &o) const { return a == o.a; }
};

using P = ExpressionParser<V>;

int main() {
    std::mt19937_64 rng(998244353);
    std::array<V, 26> vars;  // 変数 a..z の K 点でのランダムな値
    for (auto &v : vars)
        for (int i = 0; i < K; ++i) v.a[i] = rng() % MOD;

    P p;
    // 連接 = 乗算 (次の項が数字・変数・'(' で始まるときだけ継続)
    p.concat(20, P::Assoc::Left, std::multiplies<V>(),
             [](std::string_view r) {
                 std::size_t i = 0;
                 while (i < r.size() && std::isspace((unsigned char)r[i])) ++i;
                 if (i >= r.size()) return false;
                 char c = r[i];
                 return c == '(' || std::isdigit((unsigned char)c) || (c >= 'a' && c <= 'z');
             })
        .binary("+", 10, P::Assoc::Left, std::plus<V>())
        .binary("-", 10, P::Assoc::Left, std::minus<V>())
        .atom([&vars](P &q) -> V {
            char c = q.peek();
            if (c >= 'a' && c <= 'z') {
                int idx = c - 'a';
                q.advance();
                int e = 1;
                if (q.peek() == '^') {
                    q.advance();
                    e = q.peek() - '0';
                    q.advance();
                }
                V r;
                for (int i = 0; i < K; ++i) r.a[i] = 1;
                while (e--) r = r * vars[idx];
                return r;
            }
            // 非負整数リテラル (桁間に空白は入らない)
            q.peek();  // 先頭の空白を飛ばす
            V r;
            ull v = 0;
            std::size_t start = q.rest().size();
            while (std::isdigit((unsigned char)q.cur())) {
                v = (v * 10 + (q.cur() - '0')) % MOD;
                q.advance();
            }
            if (q.rest().size() == start) throw std::runtime_error("expected factor");
            for (int i = 0; i < K; ++i) r.a[i] = v;
            return r;
        });

    std::string line, correct;
    bool have_correct = false;
    while (std::getline(std::cin, line)) {
        if (line == ".") {
            if (!have_correct) break;  // 最後のブロック後の終端行
            have_correct = false;
            continue;
        }
        if (!have_correct) {
            correct = line;
            have_correct = true;
        } else {
            std::cout << (p.parse(correct) == p.parse(line) ? "yes" : "no") << '\n';
        }
    }
    return 0;
}
