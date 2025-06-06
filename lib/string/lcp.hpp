#pragma once
#include <algorithm>
#include <string>
#include <vector>

/// @brief 最長共通接頭辞
template <class T>
int longest_common_prefix(const std::vector<T> &a, const std::vector<T> &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}

/// @brief 最長共通接頭辞
int longest_common_prefix(const std::string &a, const std::string &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}
