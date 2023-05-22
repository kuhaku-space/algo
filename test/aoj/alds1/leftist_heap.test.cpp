#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_9_C"
#include "heap/leftist_heap.hpp"
#include "template/atcoder.hpp"

int main(void) {
    leftist_heap<int> heap;
    while (true) {
        string s;
        cin >> s;
        if (s == "end") {
            break;
        } else if (s == "insert") {
            int x;
            cin >> x;
            heap.push(x);
        } else {
            co(heap.top());
            heap.pop();
        }
    }

    return 0;
}
