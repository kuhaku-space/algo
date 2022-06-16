#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"
#include "fft/ntt.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    cin >> a >> b;

    auto ans = NTT<>::convolution(a, b);
    co(ans);

    return 0;
}
