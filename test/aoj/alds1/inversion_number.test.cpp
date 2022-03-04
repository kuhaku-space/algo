#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/5/ALDS1_5_D"
#include "algorithm/inversion_number.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    co(inversion_number(a));

    return 0;
}
