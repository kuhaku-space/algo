// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2704
#include <iostream>
#include "string/cfg_graph.hpp"

// Stamp Rally: 辺ラベルの列が正しい数式 (下の CNF 文法) になる s->t の歩道が
// 存在するか。文法をグラフに適用する文脈自由到達可能性 (CYK のグラフ版) で解く。
//   E -> E PT | T SF | a | LP ER | LB EB
//   T -> T SF | a | LP ER | LB EB
//   F -> a | LP ER | LB EB
//   PT -> PLUS T,  SF -> STAR F,  ER -> E RP,  EB -> E RB
//   PLUS='+', STAR='*', LP='(', RP=')', LB='[', RB=']'
// (元の文法 E->T|E+T, T->F|T*F, F->a|(E)|[E] を単位規則除去して CNF 化)
enum { E, T, F, PT, SF, ER, EB, PLUS, STAR, LP, RP, LB, RB, NUM_SYM };

int main() {
    int n, m, s, t;
    while (std::cin >> n >> m >> s >> t && (n || m || s || t)) {
        CykGraph g(n, NUM_SYM);
        for (int i = 0; i < m; ++i) {
            int a, b;
            char c;
            std::cin >> a >> b >> c;
            --a, --b;
            switch (c) {
                case 'a': g.add(E, a, b), g.add(T, a, b), g.add(F, a, b); break;
                case '+': g.add(PLUS, a, b); break;
                case '*': g.add(STAR, a, b); break;
                case '(': g.add(LP, a, b); break;
                case ')': g.add(RP, a, b); break;
                case '[': g.add(LB, a, b); break;
                case ']': g.add(RB, a, b); break;
            }
        }
        g.add_rule(E, E, PT), g.add_rule(E, T, SF), g.add_rule(E, LP, ER), g.add_rule(E, LB, EB);
        g.add_rule(T, T, SF), g.add_rule(T, LP, ER), g.add_rule(T, LB, EB);
        g.add_rule(F, LP, ER), g.add_rule(F, LB, EB);
        g.add_rule(PT, PLUS, T), g.add_rule(SF, STAR, F);
        g.add_rule(ER, E, RP), g.add_rule(EB, E, RB);
        g.solve();
        std::cout << (g.get(E, s - 1, t - 1) ? "Yes" : "No") << '\n';
    }
    return 0;
}
