#include "_base.hpp"

template <class T>
struct extended_priority_queue {
    priority_queue<T> a, b;

    bool empty() {
        return a.empty();
    }

    void insert(T x) {
        a.push(x);
    }

    T top() {
        a.top();
    }

    void pop() {
        erase(a.top());
    }

    void erase(T x) {
        b.push(x);
        while(!a.empty() && a.top() == b.top()){
            a.pop();
            b.pop();
        }
    }
};
