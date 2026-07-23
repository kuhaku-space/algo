#pragma once
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include "string/z_algorithm.hpp"

// 単体では小粒だがあると便利な小物関数をまとめたファイル

/// @brief 最長共通接頭辞 (longest common prefix)
template <class Container>
int longest_common_prefix(const Container &a, const Container &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}

/// @brief 最長共通接尾辞 (longest common suffix)
template <class Container>
int longest_common_suffix(const Container &a, const Container &b) {
    int n = (int)a.size(), m = (int)b.size(), k = std::min(n, m);
    for (int i = 0; i < k; ++i) {
        if (a[n - 1 - i] != b[m - 1 - i]) return i;
    }
    return k;
}

/// @brief s を隙間なく敷き詰める最小の周期を求める (s の長さを割り切る最小の i)
/// @complexity O(N)
template <class Container>
int minimum_period(const Container &s) {
    auto z = z_algorithm(s);
    int n = s.size();
    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0 && z[i] == n - i) return i;
    }
    return n;
}

/// @brief 回文判定
template <class Container>
bool is_palindrome(const Container &s) {
    int n = (int)s.size();
    for (int i = 0; i * 2 < n; ++i) {
        if (s[i] != s[n - 1 - i]) return false;
    }
    return true;
}

/// @brief 回文数判定
inline bool is_palindromic_number(std::int64_t x) { return is_palindrome(std::to_string(x)); }

/// @brief 正しい括弧列か判定
inline bool is_correct_parenthesis_sequences(const std::string &s) {
    int cnt = 0;
    for (char c : s) {
        if (c == '(') ++cnt;
        else if (cnt == 0) return false;
        else --cnt;
    }
    return cnt == 0;
}

/// @brief ランレングス圧縮
/// @details "aaabbc" → {(a,3),(b,2),(c,1)}
template <class Container>
auto run_length_encoding(const Container &v) {
    std::vector<std::pair<std::decay_t<decltype(*std::begin(v))>, int>> res;
    for (auto &&e : v) {
        if (res.empty() || res.back().first != e) res.emplace_back(e, 1);
        else ++res.back().second;
    }
    return res;
}

/// @brief 最長増加部分列の長さ
template <class T>
int longest_increasing_subsequence(const std::vector<T> &v, bool strict = true) {
    std::vector<T> dp;
    for (auto x : v) {
        auto it = (strict ? std::lower_bound(dp.begin(), dp.end(), x) : std::upper_bound(dp.begin(), dp.end(), x));
        if (it == dp.end()) dp.emplace_back(x);
        else *it = x;
    }
    return dp.size();
}

/// @brief 最長増加部分列を構成する添字列
template <class T>
std::vector<int> make_lis(const std::vector<T> &v) {
    int n = v.size();
    std::vector<T> dp;
    std::vector<int> pos;
    pos.reserve(n);
    for (auto x : v) {
        auto it = std::lower_bound(dp.begin(), dp.end(), x);
        pos.emplace_back(std::distance(dp.begin(), it));
        if (it == dp.end()) dp.emplace_back(x);
        else *it = x;
    }

    int x = dp.size();
    std::vector<int> res(x--);
    for (int i = n - 1; i >= 0; --i) {
        if (pos[i] == x) res[x] = i, --x;
    }
    return res;
}

/// @brief 文字列を区切り文字で分割する
inline std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> res;
    std::string cur;
    for (char c : s) {
        if (c == delim) res.emplace_back(std::exchange(cur, std::string{}));
        else cur += c;
    }
    res.emplace_back(cur);
    return res;
}

/// @brief 文字列を区切り文字で連結する
inline std::string join(const std::vector<std::string> &v, const std::string &delim = "") {
    std::string res;
    for (int i = 0; i < (int)v.size(); ++i) {
        if (i) res += delim;
        res += v[i];
    }
    return res;
}

/// @brief 辞書順で次の順列（文字列版、std::next_permutation のラッパ）
inline bool next_string(std::string &s) { return std::next_permutation(s.begin(), s.end()); }

/// @brief 全文字を小文字に変換した文字列を返す
inline std::string to_lower(std::string s) {
    for (char &c : s) c = (char)std::tolower((unsigned char)c);
    return s;
}

/// @brief 全文字を大文字に変換した文字列を返す
inline std::string to_upper(std::string s) {
    for (char &c : s) c = (char)std::toupper((unsigned char)c);
    return s;
}
