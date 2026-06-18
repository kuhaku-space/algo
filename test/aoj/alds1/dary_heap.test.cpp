// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
#include "heap/dary_heap.hpp"
#include <iostream>
#include <string>
#include "template/sonic.hpp"

int main(void) {
    // 既定の Comp = std::less<> でルートに最大値が来る最大ヒープ。
    // key は使わないので value と同じ値を入れる。
    dary_heap<int, int> heap;
    while (true) {
        std::string s;
        std::cin >> s;
        if (s == "end") {
            break;
        } else if (s == "insert") {
            int x;
            std::cin >> x;
            heap.push(x, x);
        } else {
            std::cout << heap.top().second << '\n';
            heap.pop();
        }
    }

    return 0;
}
