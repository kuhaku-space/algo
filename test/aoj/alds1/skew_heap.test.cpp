// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
#include <iostream>
#include <string>
#include "heap/meldable_heap.hpp"
#include "template/sonic.hpp"

int main(void) {
    MeldableHeap<int, std::less<>, false> heap;
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
            std::cout << heap.top() << '\n';
            heap.pop();
        }
    }

    return 0;
}
