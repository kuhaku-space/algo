#include "_base.hpp"

int64_t gcd(int64_t a, int64_t b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int64_t gcd(const vector<int64_t> &v) {
    if (v.empty()) return 1;
    int64_t res = v[0];
    for (auto i : v) res = gcd(res, i);
    return res;
}

int64_t lcm(int64_t a, int64_t b) { return a / gcd(a, b) * b; }

int64_t lcm(const vector<int64_t> &v) {
    int64_t res = 1;
    for (auto i : v) res = lcm(res, i);
    return res;
}

int64_t floor_div(int64_t p, int64_t q) {
    int64_t res = p / q;
    if (q * res > p) --res;
    return res;
}

int64_t ceil_div(int64_t p, int64_t q) {
    int64_t res = p / q;
    if (q * res < p) ++res;
    return res;
}
