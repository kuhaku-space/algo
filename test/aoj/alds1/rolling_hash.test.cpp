#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/14/ALDS1_14_B"
#include "string/rolling_hash.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    string s;
    cin >> s;

    rolling_hash rh(s);
    string t;
    cin >> t;
    for (auto e : rh.search(t)) {
        co(e);
    }

    return 0;
}
