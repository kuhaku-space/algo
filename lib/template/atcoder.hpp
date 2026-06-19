#pragma once
#include "template/template.hpp"
#include "template/sonic.hpp"
#include "template/vector.hpp"
// rep は引数の数でオーバーロードする: rep(i, n) は [0, n)、rep(i, l, r) は [l, r)。
// __VA_ARGS__ を (a, b, c, NAME, ...) に流し、4 番目のトークンで呼ぶマクロを選ぶ。
#define OVERLOAD_REP(a, b, c, NAME, ...) NAME
#define rep(...) OVERLOAD_REP(__VA_ARGS__, rep3, rep2)(__VA_ARGS__)
#define rep2(i, n) for (int i = 0; i < int(n); ++i)
#define rep3(i, l, r) for (int i = int(l); i < int(r); ++i)
#define repn(i, n) for (int i = 1; i < int(n) + 1; ++i)
#define repr(i, n) for (int i = int(n) - 1; i >= 0; --i)
#define repnr(i, n) for (int i = int(n); i >= 1; --i)
#define all(s) (s).begin(), (s).end()
using namespace std;
using ll = std::int64_t;
using ld = long double;
template <class T, class U>
std::istream &operator>>(std::istream &is, std::pair<T, U> &p) {
    return is >> p.first >> p.second;
}
template <class T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &i : v) is >> i;
    return is;
}
template <class T, class U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << '(' << p.first << ',' << p.second << ')';
}
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (auto it = v.begin(); it != v.end(); ++it) os << (it == v.begin() ? "" : " ") << *it;
    return os;
}
template <class Head, class... Tail>
void co(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cout << head << '\n';
    else std::cout << head << ' ', co(std::forward<Tail>(tail)...);
}
template <class Head, class... Tail>
void ce(Head &&head, Tail &&...tail) {
    if constexpr (sizeof...(tail) == 0) std::cerr << head << '\n';
    else std::cerr << head << ' ', ce(std::forward<Tail>(tail)...);
}
void Yes(bool is_correct = true) { std::cout << (is_correct ? "Yes\n" : "No\n"); }
void No(bool is_not_correct = true) { Yes(!is_not_correct); }
void YES(bool is_correct = true) { std::cout << (is_correct ? "YES\n" : "NO\n"); }
void NO(bool is_not_correct = true) { YES(!is_not_correct); }
void Takahashi(bool is_correct = true) { std::cout << (is_correct ? "Takahashi" : "Aoki") << '\n'; }
void Aoki(bool is_not_correct = true) { Takahashi(!is_not_correct); }
