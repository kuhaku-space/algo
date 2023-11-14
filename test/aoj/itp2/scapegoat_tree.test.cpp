#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP2_7_B"
#include "binary_tree/scapegoat_tree.hpp"
#include <iostream>

int main(void) {
    int q;
    std::cin >> q;
    int size = 0;
    scapegoat_tree<int> st;
    while (q--) {
        int x, y;
        std::cin >> x >> y;
        if (x == 0) {
            if (!st.contains(y)) st.insert(y), ++size;
            std::cout << size << std::endl;
        } else if (x == 1) {
            std::cout << st.contains(y) << std::endl;
        } else if (x == 2) {
            if (st.contains(y)) st.erase(y), --size;
        }
    }

    return 0;
}
