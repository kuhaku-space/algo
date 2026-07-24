#pragma once
#include <vector>

/// @brief Manacher
/// @details R[i] := S[i-R[i]:i] == S[i:i+R[i]]
/// @complexity 構築は $O(n)$、参照は $O(1)$
template <typename Container>
struct Manacher {
    /// @brief 列sの各中心の回文半径を構築する
    /// @complexity $O(n)$
    Manacher(const Container &_s) : _size(_s.size()), s(_s), r(_s.size()) {
        int i = 0, j = 0;
        while (i < _size) {
            while (i - j >= 0 && i + j < _size && s[i - j] == s[i + j]) ++j;
            r[i] = j;
            int k = 1;
            while (i - k >= 0 && i + k < _size && k + r[i - k] < j) r[i + k] = r[i - k], ++k;
            i += k, j -= k;
        }
    }

    /// @brief 中心iの回文半径を返す
    /// @complexity $O(1)$
    const auto &operator[](int i) const { return r[i]; }

    /// @brief 中心iの回文半径を変更可能な参照で返す
    /// @complexity $O(1)$
    auto &operator[](int i) { return r[i]; }

    /// @brief 半径列の先頭iteratorを返す
    /// @complexity $O(1)$
    const auto begin() const { return r.begin(); }

    /// @brief 半径列の先頭iteratorを返す
    /// @complexity $O(1)$
    auto begin() { return r.begin(); }

    /// @brief 半径列の終端iteratorを返す
    /// @complexity $O(1)$
    const auto end() const { return r.end(); }

    /// @brief 半径列の終端iteratorを返す
    /// @complexity $O(1)$
    auto end() { return r.end(); }

    /// @brief 回文半径列を返す
    /// @complexity $O(1)$
    const std::vector<int> &get() { return r; }

  private:
    int _size;
    const Container &s;
    std::vector<int> r;
};
