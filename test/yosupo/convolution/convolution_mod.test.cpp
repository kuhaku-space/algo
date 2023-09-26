#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"
#include "fft/ntt_mod.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    std::cin >> a >> b;
    auto ans = convolution_mod<modint107::mod()>(a, b);
    co(ans);

    return 0;
}
