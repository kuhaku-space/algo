#include "template/template.hpp"

/**
 * @brief 削除付き優先順位付きキュー
 * 
 * @tparam T 
 */
template <class T>
struct PQueue {
    bool empty() const { return this->a.empty(); }
    auto top() const { return this->a.top(); }

    void emplace(T x) { this->a.emplace(x); }
    void insert(T x) { this->a.emplace(x); }
    void push(T x) { this->a.emplace(x); }

    void pop() { this->erase(this->a.top()); }

    void erase(T x) {
        this->b.emplace(x);
        while (!this->a.empty() && this->a.top() == this->b.top()) { this->a.pop(), this->b.pop(); }
    }

  private:
    std::priority_queue<T> a, b;
};
