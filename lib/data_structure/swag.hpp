#pragma once
#include "segment_tree/monoid.hpp"
#include "template/template.hpp"

template <class M>
struct sliding_window_aggregation {
  private:
    using T = typename M::value_type;

  public:
    sliding_window_aggregation() : back_total(M::id), front(), back() {
        this->front.emplace(M::id);
    }

    T top() const { return M::op(this->back_total, this->front.top()); }

    void emplace(T val) {
        this->back.emplace(val);
        this->back_total = M::op(val, back_total);
    }
    void push(T val) { this->emplace(val); }

    void pop() {
        if (this->front.size() == 1) {
            while (!this->back.empty()) {
                this->front.emplace(M::op(this->front.top(), this->back.top()));
                this->back.pop();
            }
            this->back_total = M::id;
        }
        this->front.pop();
    }

  private:
    T back_total;
    std::stack<T> front, back;
};
