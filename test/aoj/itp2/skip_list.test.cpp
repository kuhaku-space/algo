#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B"
#include "data_structure/skip_list.hpp"
#include "template/atcoder.hpp"

int main(void) {
    int q;
    std::cin >> q;
    int size = 0;
    skip_list<int> sl;
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        if (x == 0) {
            if (!sl.contains(y)) sl.insert(y), ++size;
            co(size);
        } else if (x == 1) {
            co(sl.contains(y));
        } else if (x == 2) {
            if (sl.contains(y)) sl.erase(y), --size;
        }
    }

    return 0;
}
