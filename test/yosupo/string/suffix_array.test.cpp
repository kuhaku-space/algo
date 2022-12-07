#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include "string/suffix_array.hpp"
#include "template/atcoder.hpp"

int main(void) {
    string s;
    cin >> s;
    co(suffix_array(s));

    return 0;
}
