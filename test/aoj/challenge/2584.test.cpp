// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2584
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include "parser/parser.hpp"

// Broken Cipher Generator の文法 (文字列を返す):
//   <Cipher> ::= <String> | <Cipher><String>          (暗黙の連接)
//   <String> ::= <Letter> | '['<Cipher>']'            ('[..]' は反転)
//   <Letter> ::= '+'<Letter> | '-'<Letter> | 'A'..'Z' ('+/-' は次/前の文字)
// '?' は A-Z のいずれか。復号後が辞書順最小になるよう ? を埋める (? は 3 個以下)。
using P = ExpressionParser<std::string>;

static std::string shift(std::string s, int d) {
    for (char &c : s) {
        int x = (c - 'A' + d) % 26;
        if (x < 0) x += 26;
        c = 'A' + x;
    }
    return s;
}

static P make_parser() {
    P p;
    p.prefix("+", [](const std::string &s) { return shift(s, 1); })
        .prefix("-", [](const std::string &s) { return shift(s, -1); })
        .concat(10, P::Assoc::Left, std::plus<std::string>(),
                [](std::string_view r) {
                    std::size_t i = 0;
                    while (i < r.size() && std::isspace(static_cast<unsigned char>(r[i]))) ++i;
                    return i < r.size() && (std::isalpha(static_cast<unsigned char>(r[i])) || r[i] == '+' ||
                                            r[i] == '-' || r[i] == '[');
                })
        .atom([](P &q) -> std::string {
            if (q.consume("[")) {
                std::string in = q.parse_expression(0);
                if (!q.consume("]")) throw std::runtime_error("expected ']'");
                std::reverse(in.begin(), in.end());
                return in;
            }
            char c = q.peek();
            if (!std::isalpha(static_cast<unsigned char>(c))) throw std::runtime_error("expected letter");
            q.advance();
            return std::string(1, c);
        });
    return p;
}

int main() {
    P parser = make_parser();
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ".") break;
        std::vector<int> qpos;
        for (int i = 0; i < (int)line.size(); ++i)
            if (line[i] == '?') qpos.push_back(i);
        int k = qpos.size();
        long long total = 1;
        for (int i = 0; i < k; ++i) total *= 26;
        std::string best;
        for (long long m = 0; m < total; ++m) {
            long long t = m;
            std::string cur = line;
            for (int i = 0; i < k; ++i) {
                cur[qpos[i]] = 'A' + t % 26;
                t /= 26;
            }
            std::string dec = parser.parse(cur);
            if (best.empty() || dec < best) best = dec;
        }
        std::cout << best << '\n';
    }
    return 0;
}
