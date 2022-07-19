#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "string/z_algorithm.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string s;
    cin >> s;
    z_algorithm za(s);
    co(za.get());

    return 0;
}
