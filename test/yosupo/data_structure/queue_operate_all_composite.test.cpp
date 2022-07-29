#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "data_structure/swag.hpp"
#include "math/modint.hpp"
#include "template/atcoder.hpp"

using Mint = ModInt<>;

int main(void) {
    int q;
    cin >> q;
    sliding_window_aggregation<Affine<Mint>> swag;
    while (q--) {
        int c;
        cin >> c;
        if (c == 0) {
            int a, b;
            cin >> a >> b;
            swag.emplace({a, b});
        } else if (c == 1) {
            swag.pop();
        } else {
            int x;
            cin >> x;
            auto p = swag.top();
            co(p.first * x + p.second);
        }
    }

    return 0;
}
