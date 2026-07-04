// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1620
#include <array>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "parser/parser.hpp"

// 論理式圧縮機: 4 変数 a,b,c,d・定数 0,1・単項 -(NOT)・二項 ^(XOR) *(AND)
// (二項は必ず括弧付き) の式を、同じ真理値表を持つ最短の式の長さに変換する。
// 真理値表 (16 通り) を 16bit 値で表す。各関数を作る最短長を一度だけ DP で
// 全 65536 関数について前計算し、入力式を評価して長さを引く。
//   len(0)=len(1)=len(x)=1,  len(-X)=len(X)+1,  len((X op Y))=len(X)+len(Y)+3
using u16 = std::uint16_t;
using P = ExpressionParser<u16>;

int main() {
    constexpr int NF = 1 << 16;
    constexpr int INF = 1e9;
    constexpr int MAXL = 60;
    // 変数 a,b,c,d の真理値表 (割り当て k のビット = 対応変数の値)
    const u16 base[6] = {0x0000, 0xFFFF, 0xAAAA, 0xCCCC, 0xF0F0, 0xFF00};

    std::vector<int> dp(NF, INF);
    std::vector<std::vector<u16>> bucket(MAXL + 1);
    int found = 0;
    auto relax = [&](int f, int L) {
        if (L < dp[f]) {
            if (dp[f] == INF) ++found;
            dp[f] = L;
            bucket[L].push_back((u16)f);
        }
    };
    for (u16 b : base) relax(b, 1);
    for (int L = 2; L <= MAXL && found < NF; ++L) {
        for (u16 f : bucket[L - 1]) relax((u16)(~f), L);  // -X
        for (int lx = 1; lx + lx + 3 <= L; ++lx) {        // (X op Y): lx <= ly
            int ly = L - 3 - lx;
            if (ly < lx || ly < 1) continue;
            for (u16 fx : bucket[lx])
                for (u16 fy : bucket[ly]) {
                    relax(fx ^ fy, L);
                    relax(fx & fy, L);
                }
        }
    }

    P p;
    p.prefix("-", [](u16 x) -> u16 { return ~x; })
        .binary("^", 10, P::Assoc::Left, [](u16 a, u16 b) -> u16 { return a ^ b; })
        .binary("*", 20, P::Assoc::Left, [](u16 a, u16 b) -> u16 { return a & b; })
        .atom([&](P &q) -> u16 {
            char c = q.peek();
            q.advance();
            switch (c) {
                case '0': return 0x0000;
                case '1': return 0xFFFF;
                case 'a': return 0xAAAA;
                case 'b': return 0xCCCC;
                case 'c': return 0xF0F0;
                case 'd': return 0xFF00;
            }
            throw std::runtime_error("unexpected atom");
        });

    std::string s;
    while (std::getline(std::cin, s)) {
        if (s == ".") break;
        if (s.empty()) continue;
        std::cout << dp[p.parse(s)] << '\n';
    }
    return 0;
}
