#pragma once
#include <type_traits>
#include <utility>
#include <vector>

/// @brief ランレングス圧縮
template <class Container>
auto run_length_encoding(const Container &v) {
    std::vector<std::pair<std::decay_t<decltype(*v.begin())>, int>> res;
    for (auto &&e : v) {
        if (res.empty() || res.back().first != e) res.emplace_back(e, 1);
        else ++res.back().second;
    }
    return res;
}
