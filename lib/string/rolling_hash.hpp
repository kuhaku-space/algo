#include <random>

#include "template/template.hpp"

/**
 * @brief ローリングハッシュ
 * @details [参考](https://qiita.com/keymoon/items/11fac5627672a6d6a9f6)
 */
struct rolling_hash {
    rolling_hash(const std::string &_s) : len(_s.size() + 1), base(), data(1), p(1, 1) {
        std::mt19937 rnd((std::random_device::result_type)std::random_device()());
        this->base = rnd() + 2;
        std::uint64_t x = 0, t = 1;
        for (const auto c : _s) {
            x = this->_mod(this->_mul(x, this->base) + c);
            this->data.emplace_back(x);
            t = this->_mod(this->_mul(t, this->base));
            this->p.emplace_back(t);
        }
    }

    /**
     * @brief get hash of s[l...r]
     *
     * @param l first index
     * @param r last index
     * @return std::uint64_t
     */
    std::uint64_t get(int l, int r) const {
        return this->_mod(this->data[r] + this->mod * 4 -
                          this->_mul(this->data[l], this->p[r - l]));
    }

    /**
     * @brief search string
     *
     * @param s
     * @return std::vector<int>
     */
    std::vector<int> search(const std::string &s) {
        std::vector<int> res;
        int n = s.size();
        if (n >= this->len) return res;
        std::uint64_t x = 0;
        for (const auto c : s) x = this->_mod(this->_mul(x, this->base) + c);
        for (int i = 0; i < this->len - n; ++i) {
            if (this->get(i, i + n) == x) res.emplace_back(i);
        }
        return res;
    }

  private:
    static constexpr std::uint64_t mod = (1ul << 61) - 1;
    static constexpr std::uint64_t mask30 = (1ul << 30) - 1;
    static constexpr std::uint64_t mask31 = (1ul << 31) - 1;
    int len;
    std::uint64_t base;
    std::vector<std::uint64_t> data, p;

    constexpr std::uint64_t _mul(std::uint64_t a, std::uint64_t b) const {
        std::uint64_t au = a >> 31, ad = a & this->mask31;
        std::uint64_t bu = b >> 31, bd = b & this->mask31;
        std::uint64_t mid = ad * bu + au * bd;
        std::uint64_t midu = mid >> 30, midd = mid & this->mask30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }
    constexpr std::uint64_t _mod(std::uint64_t x) const {
        std::uint64_t xu = x >> 61, xd = x & this->mod;
        std::uint64_t res = xu + xd;
        if (res >= this->mod) res -= this->mod;
        return res;
    }
    constexpr std::uint64_t _pow(std::uint64_t x, std::uint64_t k) const {
        std::uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = this->_mod(this->_mul(res, x));
            x = this->_mod(this->_mul(x, x));
        }
        return res;
    }
};
