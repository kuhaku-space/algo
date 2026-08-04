#pragma once
#include <algorithm>
#include <cassert>
#include <limits>
#include <string>
#include <vector>
#include "string/hashint.hpp"

/// @brief ローリングハッシュ
/// @details 法 $2^{61}-1$ の Horner 法で prefix hash を持つ。
///          `base` はプログラム実行のたびに乱数で決まる（意図的な衝突を避けるため）。
/// @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
/// @see https://yosupo.hatenablog.com/entry/2023/08/06/181942
/// @complexity 構築は $O(n)$、部分文字列hashは $O(1)$
struct rolling_hash {
    /// @brief 空文字列用のhashを構築する
    /// @complexity $O(1)$
    rolling_hash() : rolling_hash(std::string()) {}

    /// @brief 文字列sのprefix hashを構築する
    /// @complexity $O(n)$
    explicit rolling_hash(const std::string &s, HashInt base = random_hash_base())
        : _size(s.size()), base(base), data(_size + 1), p(_size + 1, HashInt(1)) {
        for (int i = 0; i < _size; ++i) {
            data[i + 1] = data[i] * base + HashInt(s[i]);
            p[i + 1] = p[i] * base;
        }
    }

    /// @brief 同じ基数で別の文字列をhash化する
    /// @complexity $O(n)$
    rolling_hash derive(const std::string &s) const { return rolling_hash(s, base); }

    /// @brief 使用中の基数を返す
    /// @complexity $O(1)$
    HashInt get_base() const { return base; }

    /// @brief 文字列全体のhashを返す
    /// @complexity $O(1)$
    HashInt get() const { return data[_size]; }

    /// @brief prefix s[0,r)のhashを返す
    /// @complexity $O(1)$
    HashInt get(int r) const {
        assert(0 <= r && r <= _size);
        return data[r];
    }

    /// @brief 部分文字列s[l,r)のhashを返す
    /// @complexity $O(1)$
    HashInt get(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        return data[r] - data[l] * p[r - l];
    }

    /// @brief s.substr(pos,len)のhashを返す
    /// @complexity $O(1)$
    HashInt substr(int pos, int len = std::numeric_limits<int>::max()) const {
        assert(0 <= pos && pos <= _size);
        return get(pos, pos + std::min(len, _size - pos));
    }

    /// @brief pattern sとhashが一致する開始位置を列挙する
    /// @complexity 元文字列長を $n$、pattern長を $m$ として $O(n+m)$
    std::vector<int> search(const std::string &s) const {
        std::vector<int> res;
        int n = s.size();
        if (n > _size) return res;
        HashInt x = derive(s).get();
        for (int i = 0; i <= _size - n; ++i) {
            if (get(i, i + n) == x) res.emplace_back(i);
        }
        return res;
    }

  private:
    int _size;
    HashInt base;
    std::vector<HashInt> data, p;
};
