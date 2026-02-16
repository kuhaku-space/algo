// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/583
#include <iostream>
#include <set>
#include "data_structure/flip_set.hpp"
#include "tree/union_find.hpp"

int main(void) {
    int n, m;
    std::cin >> n >> m;
    flip_set<int> fs;
    std::set<int> st;
    union_find uf(n);
    while (m--) {
        int a, b;
        std::cin >> a >> b;
        fs.flip(a);
        fs.flip(b);
        st.emplace(a);
        st.emplace(b);
        uf.unite(a, b);
    }

    if (uf.size(*st.begin()) == (int)st.size() && fs.size() <= 2) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }

    return 0;
}
