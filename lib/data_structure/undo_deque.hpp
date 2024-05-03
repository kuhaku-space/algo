#include <deque>
#include <stack>
#include <utility>

template <class T>
struct undo_deque {
    T front() const { return data.front(); }
    T back() const { return data.back(); }
    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }

    void emplace_front(T x) {
        history.emplace(0, x);
        data.emplace_front(x);
    }

    void emplace_back(T x) {
        history.emplace(1, x);
        data.emplace_back(x);
    }

    void pop_front() {
        history.emplace(2, data.front());
        data.pop_front();
    }

    void pop_back() {
        history.emplace(3, data.back());
        data.pop_back();
    }

    void undo() {
        auto [x, y] = history.top();
        history.pop();
        if (x == 0) data.pop_front();
        else if (x == 1) data.pop_back();
        else if (x == 2) data.emplace_front(y);
        else data.emplace_back(y);
    }

    int snapshot() const { return history.size(); }

    void rollback(int x = 0) {
        while (x < (int)history.size()) undo();
    }

  private:
    std::deque<T> data;
    std::stack<std::pair<int, T>> history;
};
