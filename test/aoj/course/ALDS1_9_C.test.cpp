// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
#include <cassert>
#include <iostream>
#include <string>
#include "heap/dary_heap.hpp"
#include "heap/interval_heap.hpp"
#include "heap/meldable_heap.hpp"
#include "template/sonic.hpp"

int main(void) {
    interval_heap<int> interval;
    dary_heap<int, int> dary;
    MeldableHeap<int> leftist;
    MeldableHeap<int, std::less<>, false> skew;
    while (true) {
        std::string s;
        std::cin >> s;
        if (s == "end") {
            break;
        } else if (s == "insert") {
            int x;
            std::cin >> x;
            interval.push(x);
            dary.push(x, x);
            leftist.push(x);
            skew.push(x);
        } else {
            int x = interval.get_max();
            assert(x == dary.top().first);
            assert(x == leftist.top());
            assert(x == skew.top());
            std::cout << x << '\n';
            interval.pop_max();
            dary.pop();
            leftist.pop();
            skew.pop();
        }
    }

    return 0;
}
