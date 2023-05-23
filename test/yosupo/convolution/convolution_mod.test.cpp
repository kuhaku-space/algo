#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "fft/ntt_mod.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    cin >> a >> b;

    auto ans = convolution_mod<MOD>(a, b);
    co(ans);

    return 0;
}
