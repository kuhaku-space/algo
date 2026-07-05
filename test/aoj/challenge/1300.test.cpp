// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/1300
#include <cctype>
#include <iostream>
#include <map>
#include <numeric>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include "parser/parser.hpp"

// Chemist's Math: 化学反応式の係数を求める。各分子式を parse して元素数ベクトルに
// し、質量保存 (各元素の左右一致) を同次線形方程式 A x = 0 とみて 1 次元の零空間を
// 有理数ガウス消去で求め、正の整数・gcd=1 に正規化する。分子式は連接=元素数の加算、
// '(' … ')' に添字を掛ける ExpressionParser の例 (AOJ 1244 と同系統)。
using ll = long long;
using Map = std::map<std::string, ll>;  // 元素 → 個数
using P = ExpressionParser<Map>;

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

int main() {
    P mp;
    mp.concat(
          10, P::Assoc::Left,
          [](const Map &a, const Map &b) {
              Map r = a;
              for (auto &[k, v] : b) r[k] += v;
              return r;
          },
          [](std::string_view r) {  // 次の group は英大文字か '(' で始まる
              for (char c : r) {
                  if (std::isspace((unsigned char)c)) continue;
                  return std::isupper((unsigned char)c) || c == '(';
              }
              return false;
          })
        .no_group()
        .atom([](P &q) -> Map {
            Map m;
            char c = q.peek();
            if (c == '(') {
                q.advance();
                m = q.parse_expression(0);
                if (!q.consume(")")) throw std::runtime_error("expected )");
            } else {  // 元素: 大文字 + 小文字列
                std::string name(1, c);
                q.advance();
                while (std::islower((unsigned char)q.cur())) name += q.cur(), q.advance();
                m[name] = 1;
            }
            if (std::isdigit((unsigned char)q.peek())) {  // 添字
                ll n = q.read_uint();
                for (auto &[k, v] : m) v *= n;
            }
            return m;
        });

    auto split = [](const std::string &s, char sep) {
        std::vector<std::string> out;
        std::string cur;
        for (char c : s) {
            if (c == sep) out.push_back(cur), cur.clear();
            else cur += c;
        }
        out.push_back(cur);
        return out;
    };

    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == ".") break;
        if (line.empty()) continue;
        line.pop_back();  // 末尾の '.'
        std::size_t arrow = line.find("->");
        auto lhs = split(line.substr(0, arrow), '+');
        auto rhs = split(line.substr(arrow + 2), '+');

        int C = (int)(lhs.size() + rhs.size());  // 未知の係数の数 (= 分子数)
        std::map<std::string, int> eidx;         // 元素 → 行
        std::vector<std::vector<Frac>> M;
        auto elem_row = [&](const std::string &e) -> int {
            auto it = eidx.find(e);
            if (it != eidx.end()) return it->second;
            int r = (int)M.size();
            eidx[e] = r;
            M.emplace_back(C, Frac(0));
            return r;
        };
        for (int j = 0; j < (int)lhs.size(); ++j)
            for (auto &[e, cnt] : mp.parse(lhs[j])) M[elem_row(e)][j] = Frac(cnt);
        for (int j = 0; j < (int)rhs.size(); ++j)
            for (auto &[e, cnt] : mp.parse(rhs[j])) M[elem_row(e)][lhs.size() + j] = Frac(-cnt);

        // 有理数ガウス消去で RREF、ピボット列を記録
        int R = (int)M.size();
        std::vector<int> pivot_col(R, -1);
        std::vector<bool> is_pivot(C, false);
        int row = 0;
        for (int col = 0; col < C && row < R; ++col) {
            int sel = -1;
            for (int i = row; i < R; ++i)
                if (!M[i][col].zero()) {
                    sel = i;
                    break;
                }
            if (sel < 0) continue;
            std::swap(M[row], M[sel]);
            Frac inv = Frac(1) / M[row][col];
            for (int c = 0; c < C; ++c) M[row][c] = M[row][c] * inv;
            for (int i = 0; i < R; ++i)
                if (i != row && !M[i][col].zero()) {
                    Frac f = M[i][col];
                    for (int c = 0; c < C; ++c) M[i][c] = M[i][c] - f * M[row][c];
                }
            pivot_col[row] = col;
            is_pivot[col] = true;
            ++row;
        }
        int freecol = -1;
        for (int c = 0; c < C; ++c)
            if (!is_pivot[c]) freecol = c;  // 零空間は 1 次元 (最後の自由変数)

        // 自由変数 = 1、ピボット変数を後退代入
        std::vector<Frac> x(C, Frac(0));
        x[freecol] = Frac(1);
        for (int r = 0; r < row; ++r) x[pivot_col[r]] = Frac(0) - M[r][freecol];

        // 分母を払って整数化、gcd=1・正に正規化
        ll L = 1;
        for (auto &f : x) L = std::lcm(L, f.d);
        std::vector<ll> xi(C);
        for (int c = 0; c < C; ++c) xi[c] = x[c].n * (L / x[c].d);
        if (xi[0] < 0)
            for (ll &v : xi) v = -v;
        ll g = 0;
        for (ll v : xi) g = std::gcd(g, v);
        for (ll &v : xi) v /= g;

        for (int c = 0; c < C; ++c) std::cout << (c ? " " : "") << xi[c];
        std::cout << '\n';
    }
    return 0;
}
