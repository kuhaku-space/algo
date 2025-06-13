#pragma once
#include <set>
#include <utility>

/// @brief flip set
template <class T>
struct flip_set {
    flip_set() : data() {}

    const auto begin() const { return data.begin(); }
    auto begin() { return data.begin(); }
    const auto end() const { return data.end(); }
    auto end() { return data.end(); }

    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }

    bool contains(const T &x) const { return data.count(x); }
    bool contains(T &&x) const { return data.count(std::move(x)); }

    bool flip(const T &x) {
        if (data.count(x)) return data.erase(x), false;
        else return data.emplace(x), true;
    }
    bool flip(T &&x) {
        if (data.count(x)) return data.erase(std::move(x)), false;
        else return data.emplace(x), true;
    }

  private:
    std::set<T> data;
};
