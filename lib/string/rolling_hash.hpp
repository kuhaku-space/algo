#include <random>

#include "template/template.hpp"

/**
 * @brief ローリングハッシュ
 *
 * @ref https://qiita.com/keymoon/items/11fac5627672a6d6a9f6 "参考"
 */
struct rolling_hash {
    rolling_hash(const string &_s) : data(1), p(1, 1), len(_s.size() + 1) {
        random_device seed;
        mt19937 mt(seed());
        this->base = mt() + 2;
        uint64_t x = 0, t = 1;
        for (const auto c : _s) {
            x = this->_mod(this->_mul(x, this->base) + c);
            this->data.emplace_back(x);
            t = this->_mod(this->_mul(t, this->base));
            this->p.emplace_back(t);
        }
    }

    constexpr uint64_t get(int l, int r) {
        return this->_mod(this->data[r] + this->mod * 4 -
                          this->_mul(this->data[l], this->p[r - l]));
    }

    vector<int> search(const string &s) {
        vector<int> res;
        int n = s.size();
        if (n >= this->len) return res;
        uint64_t x = 0;
        for (const auto c : s) x = this->_mod(this->_mul(x, this->base) + c);
        for (int i = n; i < len; ++i) {
            if (this->get(i - n, i) == x) res.emplace_back(i - n);
            x = this->_mod(this->_mul(x, this->base));
        }
        return res;
    }

  private:
    static constexpr uint64_t mod = (1ul << 61) - 1;
    static constexpr uint64_t mask30 = (1ul << 30) - 1;
    static constexpr uint64_t mask31 = (1ul << 31) - 1;
    uint64_t base, len;
    vector<uint64_t> data, p;

    constexpr uint64_t _mul(uint64_t a, uint64_t b) const {
        uint64_t au = a >> 31, ad = a & this->mask31;
        uint64_t bu = b >> 31, bd = b & this->mask31;
        uint64_t mid = ad * bu + au * bd;
        uint64_t midu = mid >> 30, midd = mid & this->mask30;
        return au * bu * 2 + midu + (midd << 31) + ad * bd;
    }
    constexpr uint64_t _mod(uint64_t x) const {
        uint64_t xu = x >> 61, xd = x & this->mod;
        uint64_t res = xu + xd;
        if (res >= this->mod) res -= this->mod;
        return res;
    }
    constexpr uint64_t _pow(uint64_t x, uint64_t k) const {
        uint64_t res = 1;
        for (; k; k >>= 1) {
            if (k & 1) res = this->_mod(this->_mul(res, x));
            x = this->_mod(this->_mul(x, x));
        }
        return res;
    }
};
