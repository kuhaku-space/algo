// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1087
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "parser/parser.hpp"

// Dimensional Analysis: 基本量 n 個の次元ベクトルで各量を表す。式 (+ - * /・括弧・
// 変数) を評価し、結果の次元に一致する組立量名を答える (複数なら最後に定義した方、
// 無ければ undefined)。次元が異なる量の加減は「不正な演算」で error。
// 値型を「次元ベクトル + エラーフラグ」にした ExpressionParser の例。
constexpr int MAXN = 5;
struct Dim {
    std::array<int, MAXN> e{};
    bool err = false;
};
using P = ExpressionParser<Dim>;

int main() {
    int n, m, p;
    while (std::cin >> n >> m >> p && (n || m || p)) {
        std::map<std::string, Dim> derived;                    // 変数割り当て用 (名前 → 次元)
        std::map<std::array<int, MAXN>, std::string> name_of;  // 次元 → 名前 (後勝ち)
        for (int i = 0; i < m; ++i) {
            std::string name;
            std::cin >> name;
            Dim d;
            for (int j = 0; j < n; ++j) std::cin >> d.e[j];
            derived[name] = d;
            name_of[d.e] = name;  // 同じ次元が複数あれば最後に定義した名前で上書き
        }
        std::string formula;
        std::cin >> formula;
        std::map<std::string, Dim> var;  // 変数名 → 次元
        for (int i = 0; i < p; ++i) {
            std::string v, dname;
            std::cin >> v >> dname;
            var[v] = derived[dname];
        }

        auto add_sub = [](const Dim &a, const Dim &b) {
            Dim r = a;
            r.err = a.err || b.err || a.e != b.e;  // 次元不一致は不正な演算
            return r;
        };
        P parser;
        parser.binary("+", 10, P::Assoc::Left, add_sub)
            .binary("-", 10, P::Assoc::Left, add_sub)
            .binary("*", 20, P::Assoc::Left,
                    [](const Dim &a, const Dim &b) {
                        Dim r;
                        r.err = a.err || b.err;
                        for (int i = 0; i < MAXN; ++i) r.e[i] = a.e[i] + b.e[i];
                        return r;
                    })
            .binary("/", 20, P::Assoc::Left,
                    [](const Dim &a, const Dim &b) {
                        Dim r;
                        r.err = a.err || b.err;
                        for (int i = 0; i < MAXN; ++i) r.e[i] = a.e[i] - b.e[i];
                        return r;
                    })
            .atom([&var](P &q) -> Dim {
                std::string_view id = q.read_identifier();
                return var[std::string(id)];
            });

        Dim res = parser.parse(formula);
        if (res.err) {
            std::cout << "error\n";
        } else if (auto it = name_of.find(res.e); it != name_of.end()) {
            std::cout << it->second << '\n';
        } else {
            std::cout << "undefined\n";
        }
    }
    return 0;
}
