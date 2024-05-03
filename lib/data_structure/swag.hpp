#pragma once
#include <stack>
#include "segment_tree/monoid.hpp"

template <class M>
struct sliding_window_aggregation {
  private:
    using T = typename M::value_type;

  public:
    sliding_window_aggregation() : back_total(M::id), front(), back() { front.emplace(M::id); }

    T top() const { return M::op(back_total, front.top()); }

    void emplace(T val) {
        back.emplace(val);
        back_total = M::op(val, back_total);
    }
    void push(T val) { emplace(val); }

    void pop() {
        if (front.size() == 1) {
            while (!back.empty()) {
                front.emplace(M::op(front.top(), back.top()));
                back.pop();
            }
            back_total = M::id;
        }
        front.pop();
    }

  private:
    T back_total;
    std::stack<T> front, back;
};
