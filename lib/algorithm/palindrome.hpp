#pragma once
#include <cstdint>
#include <string>
#include <vector>

/// 回文判定
template <class T>
bool is_palindrome(const std::vector<T> &v) {
    int n = v.size();
    for (int i = 0; i < n / 2; ++i) {
        if (v[i] != v[n - 1 - i])
            return false;
    }
    return true;
}

/// 回文判定
bool is_palindrome(const std::string &s) {
    int n = s.size();
    for (int i = 0; i < n / 2; ++i) {
        if (s[i] != s[n - 1 - i])
            return false;
    }
    return true;
}

/// 回文数判定
bool is_palindromic_number(std::int64_t x) {
    return is_palindrome(std::to_string(x));
}
