#include "template/template.hpp"

template <class T>
struct undo_deque {
    T front() const { return this->data.front(); }
    T back() const { return this->data.back(); }
    bool empty() const { return this->data.empty(); }
    int size() const { return this->data.size(); }

    void emplace_front(T x) {
        this->history.emplace(0, x);
        this->data.emplace_front(x);
    }

    void emplace_back(T x) {
        this->history.emplace(1, x);
        this->data.emplace_back(x);
    }

    void pop_front() {
        this->history.emplace(2, this->data.front());
        this->data.pop_front();
    }

    void pop_back() {
        this->history.emplace(3, this->data.back());
        this->data.pop_back();
    }

    void undo() {
        auto [x, y] = this->history.top();
        this->history.pop();
        if (x == 0) this->data.pop_front();
        else if (x == 1) this->data.pop_back();
        else if (x == 2) this->data.emplace_front(y);
        else this->data.emplace_back(y);
    }

    int snapshot() const { return this->history.size(); }

    void rollback(int x = 0) {
        while (x < (int)this->history.size()) this->undo();
    }

  private:
    std::deque<T> data;
    std::stack<std::pair<int, T>> history;
};
