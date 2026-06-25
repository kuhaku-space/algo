// competitive-verifier: PROBLEM https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C
#include <iostream>
#include <string>
#include "heap/dary_heap.hpp"
#include "template/sonic.hpp"

int main(void) {
    // 既定の Comp = std::less<> でルートに最大値が来る最大ヒープ。
    // 順序基準 key で比較する。付随データ value は使わないので key と同じ値を入れる。
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
            std::cout << heap.top().first << '\n';
            heap.pop();
        }
    }

    return 0;
}
