#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/2934"
#include "string/manacher.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n;
    cin >> n;
    string s;
    cin >> s;

    if (n == 1) {
        co(1);
        return 0;
    }

    Manacher ma(s);

    repn (m, n) {
        bool flag = true;
        int k = m;
        while (k < n) {
            flag &= ma[k] >= min(m + 1, n - k);
            k += m;
        }
        if (flag) {
            co(m + 1);
            break;
        }
    }

    return 0;
}
