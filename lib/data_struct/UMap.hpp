#include "template/template.hpp"

template <class Key, class Val>
struct UMap {
    unordered_map<Key, Val> data;
    Val e;

    UMap(Val _e = Val()) : e(_e), data() {}

    Val &operator[](Key k) {
        if (data.find(k) == data.end()) data[k] = e;
        return data[k];
    }

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }

    auto find() { return data.find(); }

    auto erase(Val v) { return data.erase(v); }
};
