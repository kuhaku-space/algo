// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2857
#include <array>
#include <iostream>
#include <map>
#include <string>
#include "parser/parser.hpp"

// Tournament Chart: トーナメント表 (BNF: winner ::= person | "[" winner "-" winner "]")
// を parse し、各人の勝利数申告が矛盾なく実現可能か判定する。
// 部分木を評価すると「その部分木の優勝者になれる人 → 部分木内での勝利数」の
// マップが得られる (負けた人の申告は途中で確定・検証済み)。group '[' ']' と
// 二項 '-' で木を組み立てる ExpressionParser の例。
using Map = std::map<char, int>;  // 優勝者候補 → 部分木内で勝った回数
using P = ExpressionParser<Map>;

int main() {
    std::array<int, 26> v{};  // 各人の申告勝利数
    std::string s;
    std::getline(std::cin, s);
    char ch;
    int val;
    while (std::cin >> ch >> val) v[ch - 'a'] = val;

    P p;
    p.group('[', ']')
        .binary("-", 10, P::Assoc::Left,
                [&v](const Map &L, const Map &R) -> Map {
                    // 一方が「きれいに敗退できる」= 優勝者候補の申告が部分木勝利数と一致
                    auto can_lose = [&](const Map &m) {
                        for (auto &[c, w] : m)
                            if (v[c - 'a'] == w) return true;
                        return false;
                    };
                    Map res;
                    if (can_lose(R))  // R が敗退 → L 側の候補が 1 勝上乗せして勝ち上がる
                        for (auto &[c, w] : L) res[c] = w + 1;
                    if (can_lose(L))
                        for (auto &[c, w] : R) res[c] = w + 1;
                    return res;
                })
        .atom([](P &q) -> Map {
            char c = q.peek();
            q.advance();
            return {{c, 0}};
        });

    Map root = p.parse(s);
    bool ok = false;
    for (auto &[c, w] : root)  // 優勝者の申告が全勝利数と一致すれば実現可能
        if (v[c - 'a'] == w) ok = true;
    std::cout << (ok ? "Yes" : "No") << '\n';
    return 0;
}
