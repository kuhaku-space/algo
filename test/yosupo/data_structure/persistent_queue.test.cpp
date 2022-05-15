#define PROBLEM "https://judge.yosupo.jp/problem/persistent_queue"
#include "data_structure/persistent_queue.hpp"
#include "template/atcoder.hpp"

int main(void) {
    sonic();
    int q;
    cin >> q;
    vector<persistent_queue<int>> qs;
    qs.emplace_back();

    rep (i, q) {
        int t;
        cin >> t;
        if (t == 0) {
            int k, x;
            cin >> k >> x;
            qs.emplace_back(qs[k + 1].push(x));
        } else {
            int k;
            cin >> k;
            co(qs[k + 1].top());
            qs.emplace_back(qs[k + 1].pop());
        }
    }

    return 0;
}
