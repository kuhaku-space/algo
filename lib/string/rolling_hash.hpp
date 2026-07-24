#pragma once
#include <cassert>
#include <cstdint>
#include <limits>
#include <random>
#include <string>
#include <vector>

/// @brief ローリングハッシュ
/// @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
/// @see https://yosupo.hatenablog.com/entry/2023/08/06/181942
/// @complexity 構築は $O(n)$、部分文字列hashは $O(1)$
struct rolling_hash {
    /// @brief 空文字列用のhashを乱数基数で構築する
    /// @complexity $O(1)$
    rolling_hash() : _size(), base((std::uint64_t)std::random_device()() + 2), data(), p() {}

    /// @brief 文字列sのprefix hashを基数baseで構築する
    /// @complexity $O(n)$
    rolling_hash(const std::string &_s, std::uint64_t base = (std::uint64_t)std::random_device()() + 2)
        : _size(_s.size()), base(base), data(1), p(1, 1) {
        std::uint64_t x = 0, t = 1, y;
        for (const auto c : _s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
            data.emplace_back(x);
            t = _mul(t, base);
            p.emplace_back(t);
        }
    }

    /// @brief 使用中の基数を返す
    /// @complexity $O(1)$
    std::uint64_t get_base() const { return base; }

    /// @brief prefix s[0,r)のhashを返す
    /// @complexity $O(1)$
    std::uint64_t get(int r) const { return data[r]; }

    /// @brief 部分文字列s[l,r)のhashを返す
    /// @complexity $O(1)$
    std::uint64_t get(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        std::uint64_t x = data[r] + mod - _mul(data[l], p[r - l]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }

    /// @brief s.substr(pos,len)のhashを返す
    /// @complexity $O(1)$
    std::uint64_t substr(int pos, int len = std::numeric_limits<int>::max()) const {
        assert(0 <= pos && pos <= _size);
        len = std::min(len, _size - pos);
        std::uint64_t x = data[pos + len] + mod - _mul(data[pos], p[len]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }

    /// @brief pattern sとhashが一致する開始位置を列挙する
    /// @complexity 元文字列長を $n$、pattern長を $m$ として $O(n+m)$
    std::vector<int> search(const std::string &s) {
        std::vector<int> res;
        int n = s.size();
        if (n > _size) return res;
        std::uint64_t x = 0, y;
        for (char c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        for (int i = 0; i <= _size - n; ++i) {
            if (get(i, i + n) == x) res.emplace_back(i);
        }
        return res;
    }

    /// @brief 同じ基数で文字列sのhashを計算する
    /// @complexity $O(n)$
    std::uint64_t hash(const std::string &s) const {
        std::uint64_t x = 0, y;
        for (const auto c : s) {
            x = _mul(x, base) + c;
            x = (__builtin_usubl_overflow(x, mod, &y) ? x : y);
        }
        return x;
    }

  private:
    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    int _size;
    std::uint64_t base;
    std::vector<std::uint64_t> data, p;

    constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t b) const {
        __uint128_t t = (__uint128_t)a * b;
        a = (t >> 61) + (t & mod);
        return __builtin_usubl_overflow(a, mod, &b) ? a : b;
    }
    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const {
        std::uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = _mul(res, x);
            x = _mul(x, x);
        }
        return res;
    }
};
