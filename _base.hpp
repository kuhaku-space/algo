#include <bits/stdc++.h>
using namespace std;
template <class T1, class T2>
bool chmax(T1 &a, const T2 b) {
    return a < b ? a = b, true : false;
}
template <class T1, class T2>
bool chmin(T1 &a, const T2 b) {
    return a > b ? a = b, true : false;
}
constexpr int64_t INF = 1000000000000000001;
constexpr int64_t MOD = 1000000007;
constexpr int64_t MOD_N = 998244353;
constexpr double EPS = 1e-11;
const double PI = acos(-1.0);