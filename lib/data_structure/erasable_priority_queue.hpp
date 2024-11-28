#include <functional>
#include <queue>
#include <utility>

/// @brief 削除可能優先度付きキュー
template <class T, class Comp = std::less<>>
struct erasable_priority_queue {
    bool empty() const { return a.empty(); }
    int size() const { return a.size() - b.size(); }
    T top() const { return a.top(); }

    void insert(const T &x) { a.push(x); }
    void insert(T &&x) { a.push(std::move(x)); }
    void push(const T &x) { a.push(x); }
    void push(T &&x) { a.push(std::move(x)); }
    template <typename... Args>
    void emplace(Args &&...args) {
        a.emplace(std::forward<Args>(args)...);
    }

    void pop() { erase(a.top()); }

    void erase(const T &x) {
        b.push(x);
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }
    void erase(T &&x) {
        b.push(std::move(x));
        while (!b.empty() && a.top() == b.top()) { a.pop(), b.pop(); }
    }

  private:
    std::priority_queue<T, std::vector<T>, Comp> a, b;
};
