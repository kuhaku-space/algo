// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/2596
// competitive-verifier: ERROR 0.00000001
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include "parser/parser.hpp"

// Points and Lines: 唯一の左結合演算子 '@' が、被演算子の型 (点 or 直線) で
// 意味を変える式を評価する。点@点=2点を通る直線、直線@直線=交点、
// 点@直線/直線@点=直線に関する点の対称点。値型を「点 or 直線」の直和にした例。
// リテラルは常に "(X,Y)" (座標) か "(...)" (グループ化) なので、'(' の直後が
// 数字なら座標、'(' ならグループと判別できる。'(' は自前処理 (no_group)。
struct Val {
    bool is_point;
    double x, y;    // 点、または直線上の 1 点
    double dx, dy;  // 直線の方向ベクトル
};
using P = ExpressionParser<Val>;

static Val point(double x, double y) { return {true, x, y, 0, 0}; }

int main() {
    P p;
    p.binary("@", 10, P::Assoc::Left,
             [](const Val &a, const Val &b) -> Val {
                 if (a.is_point && b.is_point)  // 2 点を通る直線
                     return {false, a.x, a.y, b.x - a.x, b.y - a.y};
                 if (!a.is_point && !b.is_point) {  // 2 直線の交点
                     double den = a.dx * b.dy - a.dy * b.dx;
                     double s = ((b.x - a.x) * b.dy - (b.y - a.y) * b.dx) / den;
                     return point(a.x + s * a.dx, a.y + s * a.dy);
                 }
                 const Val &pt = a.is_point ? a : b;  // 直線に関する点の対称点
                 const Val &ln = a.is_point ? b : a;
                 double t = ((pt.x - ln.x) * ln.dx + (pt.y - ln.y) * ln.dy) / (ln.dx * ln.dx + ln.dy * ln.dy);
                 double fx = ln.x + t * ln.dx, fy = ln.y + t * ln.dy;
                 return point(2 * fx - pt.x, 2 * fy - pt.y);
             })
        .no_group()
        .atom([](P &q) -> Val {
            if (q.peek() != '(') throw std::runtime_error("expected (");
            q.advance();
            if (q.peek() == '(') {  // グループ化 "(" <expr> ")"
                Val v = q.parse_expression(0);
                if (!q.consume(")")) throw std::runtime_error("expected )");
                return v;
            }
            // 座標 "(" <number> "," <number> ")"
            auto num = [&q] {
                q.peek();
                double sign = 1;
                if (q.cur() == '-') sign = -1, q.advance();
                return sign * (double)q.read_uint();
            };
            double x = num();
            if (!q.consume(",")) throw std::runtime_error("expected ,");
            double y = num();
            if (!q.consume(")")) throw std::runtime_error("expected )");
            return point(x, y);
        });

    std::cout << std::fixed << std::setprecision(8);
    std::string s;
    while (std::getline(std::cin, s)) {
        if (s == "#") break;
        if (s.empty()) continue;
        Val r = p.parse(s);
        std::cout << r.x << ' ' << r.y << '\n';
    }
    return 0;
}
