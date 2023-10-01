#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C"
#include "heap/skew_heap.hpp"
#include <iostream>
#include <string>

int main(void) {
    skew_heap<int> heap;
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
            std::cout << heap.top() << std::endl;
            heap.pop();
        }
    }

    return 0;
}
