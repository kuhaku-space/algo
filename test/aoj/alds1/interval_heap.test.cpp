// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
#include "heap/interval_heap.hpp"
#include <iostream>
#include <string>

int main(void) {
    interval_heap<int> heap;
    while (true) {
        std::string s;
        std::cin >> s;
        if (s == "end") {
            break;
        } else if (s == "insert") {
            int x;
            std::cin >> x;
            heap.push(x);
        } else {
            std::cout << heap.get_max() << std::endl;
            heap.pop_max();
        }
    }

    return 0;
}
