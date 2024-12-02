#pragma once
#include <cassert>
#include <functional>
#include <utility>
#include "data_structure/erasable_priority_queue.hpp"

template <typename T, class Comp, class RComp>
struct priority_k_sum {
    priority_k_sum(int k) : _k(k), _sum() { assert(_k >= 0); }

    int size() const { return in.size() + out.size(); }

    T query() const { return _sum; }
    T sum() const { return _sum; }

    int get_k() const { return _k; }

    void set_k(int x) {
        assert(x >= 0);
        _k = x;
        modify();
    }

    void insert(const T &x) {
        _sum += x, in.emplace(x);
        modify();
    }
    void insert(T &&x) {
        _sum += x, in.emplace(std::move(x));
        modify();
    }

    void erase(const T &x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) _sum -= x, in.erase(x);
        else out.erase(x);
        modify();
    }
    void erase(T &&x) {
        assert(size());
        if (!in.empty() && !Comp()(in.top(), x)) _sum -= x, in.erase(std::move(x));
        else out.erase(std::move(x));
        modify();
    }

  private:
    int _k;
    T _sum;
    erasable_priority_queue<T, Comp> in;
    erasable_priority_queue<T, RComp> out;
    void modify() {
        while (in.size() < _k && !out.empty()) {
            auto p = out.top();
            _sum += p, in.emplace(p);
            out.pop();
        }
        while (in.size() > _k) {
            auto p = in.top();
            _sum -= p, out.emplace(p);
            in.pop();
        }
    }
};

template <typename T>
using maximum_sum = priority_k_sum<T, std::greater<T>, std::less<T>>;
template <typename T>
using minimum_sum = priority_k_sum<T, std::less<T>, std::greater<T>>;
