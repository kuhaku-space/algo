#pragma once
#include <cassert>
#include <cstdint>
#include <limits>
#include <random>
#include <string>
#include <vector>

/**
 * @brief ローリングハッシュ
 * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 * @see https://yosupo.hatenablog.com/entry/2023/08/06/181942
 */
struct rolling_hash {
    rolling_hash() : _size(), base((std::uint64_t)std::random_device()() + 2), data(), p() {}

    rolling_hash(const std::string &_s, uint64_t base = (std::uint64_t)std::random_device()() + 2)
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

    std::uint64_t get_base() const { return base; }

    /// get hash of s[0...r]
    std::uint64_t get(int r) const { return data[r]; }

    /// get hash of s[l...r]
    std::uint64_t get(int l, int r) const {
        assert(0 <= l && l <= r && r <= _size);
        std::uint64_t x = data[r] + mod - _mul(data[l], p[r - l]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }

    /// get hash of s.substr(pos, len)
    std::uint64_t substr(int pos, int len = std::numeric_limits<int>::max()) const {
        assert(0 <= pos && pos <= _size);
        len = std::min(len, _size - pos);
        std::uint64_t x = data[pos + len] + mod - _mul(data[pos], p[len]), y;
        return __builtin_usubl_overflow(x, mod, &y) ? x : y;
    }

    /// search string
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
