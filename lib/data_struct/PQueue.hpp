#include "_base.hpp"

template <class T>
struct PQueue {
    priority_queue<T> a, b;

    bool empty() const { return a.empty(); }

    void insert(T x) { a.push(x); }

    T top() const { a.top(); }

    void pop() { erase(a.top()); }

    void erase(T x) {
        b.push(x);
        while (!a.empty() && a.top() == b.top()) {
            a.pop(), b.pop();
        }
    }
};
