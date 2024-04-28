#include <cstdint>
#include "fft/ntt.hpp"
#include "template/template.hpp"

/**
 * @brief 多倍長整数
 *
 * @see https://qiita.com/square1001/items/1aa12e04934b6e749962
 * @see http://yamatyuu.net/computer/program/long/div/index.html
 */
struct BigInt {
    BigInt() : data(1), sign() {}
    explicit BigInt(std::int64_t x) : data(), sign() {
        if (!x) {
            this->data = std::vector<int>(1);
            return;
        }
        bool flag = x < 0;
        if (x < 0) x = -x;
        std::vector<int> v;
        while (x) {
            v.emplace_back(x % 10);
            x /= 10;
        }
        this->sign = flag;
        this->data = v;
    }
    explicit BigInt(std::string s) : data(s.size()), sign(false) {
        if (s[0] == '-') {
            this->sign = true;
            this->data.pop_back();
        }
        std::reverse(s.begin(), s.end());
        for (int i = 0; i < (int)s.size() - int(this->sign); ++i) { this->data[i] = s[i] - '0'; }
    }
    explicit BigInt(const std::vector<int> &v) : data(v) { this->format(); }
    explicit BigInt(const std::vector<int> &v, bool flag) : data(v), sign(flag) { this->format(); }

    BigInt &operator+=(const BigInt &rhs) {
        if (this->sign == rhs.sign) add(this->data, rhs.data);
        else sub(this->data, rhs.data);
        this->format();
        return *this;
    }
    BigInt &operator-=(const BigInt &rhs) {
        if (sign == rhs.sign) sub(this->data, rhs.data);
        else add(this->data, rhs.data);
        this->format();
        return *this;
    }
    BigInt &operator*=(const BigInt &rhs) {
        this->mul(this->data, rhs.data);
        this->sign ^= rhs.sign;
        this->format();
        return *this;
    }
    BigInt &operator*=(int rhs) {
        this->mul(this->data, rhs);
        return *this;
    }
    BigInt &operator/=(const BigInt &rhs) {
        assert(!rhs.is_zero());
        if (this->abs_less(rhs)) return (*this = BigInt());
        if (this->size() < 9) return (*this = BigInt(this->to_int() / rhs.to_int()));
        if (rhs.size() < 8) return (*this /= rhs.to_int());
        std::vector<int> v = rhs.data;
        int k = 10 / (1 + v.back());
        *this *= k;
        this->mul(v, k);
        int d = this->size() - v.size();
        std::vector<int> u(this->data.end() - v.size() + 1, this->data.end());
        std::vector<int> ans(d + 1);
        for (int i = d; i >= 0; --i) {
            u.insert(u.begin(), this->data[i]);
            if (u.size() > v.size()) {
                int x = 0, y = 0;
                for (int j = 0; j < 3; ++j) x = x * 10 + u[(int)u.size() - 1 - j];
                for (int j = 0; j < 2; ++j) y = y * 10 + v[(int)v.size() - 1 - j];
                int z = x / y - 1;
                auto cp = v;
                this->mul(cp, z);
                this->sub(u, cp);
                ans[i] = z;
            }
            if (!this->less(u, v)) {
                this->sub(u, v);
                ++ans[i];
            }
        }

        return (*this = BigInt(ans, this->sign != rhs.sign));
    }
    BigInt &operator/=(int rhs) {
        bool flag = rhs < 0;
        if (rhs < 0) rhs = -rhs;
        int x = 0;
        std::vector<int> ans(this->size());
        for (int i = this->size() - 1; i >= 0; --i) {
            x = x * 10 + this->data[i];
            ans[i] = x / rhs;
            x -= ans[i] * rhs;
        }
        return (*this = BigInt(ans, this->sign != flag));
    }
    BigInt &operator%=(const BigInt &rhs) {
        assert(!rhs.is_zero());
        if (this->abs_less(rhs)) return *this;
        if (this->size() < 9) return (*this = BigInt(this->to_int() % rhs.to_int()));
        if (rhs.size() < 8) return (*this %= rhs.to_int());
        std::vector<int> v = rhs.data;
        int k = 10 / (1 + v.back());
        *this *= k;
        this->mul(v, k);
        int d = this->size() - v.size();
        std::vector<int> u(this->data.end() - v.size() + 1, this->data.end());
        for (int i = d; i >= 0; --i) {
            u.insert(u.begin(), this->data[i]);
            if (u.size() > v.size()) {
                int x = 0, y = 0;
                for (int j = 0; j < 3; ++j) x = x * 10 + u[(int)u.size() - 1 - j];
                for (int j = 0; j < 2; ++j) y = y * 10 + v[(int)v.size() - 1 - j];
                int z = x / y - 1;
                auto cp = v;
                this->mul(cp, z);
                this->sub(u, cp);
            }
            if (!this->less(u, v)) this->sub(u, v);
        }

        this->div(u, k);
        return (*this = BigInt(u, this->sign != rhs.sign));
    }
    BigInt &operator%=(int rhs) {
        bool flag = rhs < 0;
        if (rhs < 0) rhs = -rhs;
        int x = 0;
        for (int i = this->size() - 1; i >= 0; --i) {
            x = x * 10 + this->data[i];
            int k = x / rhs;
            x -= k * rhs;
        }
        return (*this = (this->sign != flag ? BigInt(-x) : BigInt(x)));
    }

    BigInt &operator>>=(int rhs) {
        this->data.erase(this->data.begin(), this->data.begin() + rhs);
        return *this;
    }
    BigInt &operator<<=(int rhs) {
        this->data.insert(this->data.begin(), rhs, 0);
        return *this;
    }

    BigInt operator-() const {
        BigInt res = *this;
        if (!res.is_zero()) res.sign = !res.sign;
        return res;
    }
    BigInt operator+(const BigInt &rhs) const { return BigInt(*this) += rhs; }
    BigInt operator-(const BigInt &rhs) const { return BigInt(*this) -= rhs; }
    BigInt operator*(const BigInt &rhs) const { return BigInt(*this) *= rhs; }
    BigInt operator*(int rhs) const { return BigInt(*this) *= rhs; }
    BigInt operator/(const BigInt &rhs) const { return BigInt(*this) /= rhs; }
    BigInt operator%(const BigInt &rhs) const { return BigInt(*this) %= rhs; }

    bool operator==(const BigInt &rhs) const {
        if (this->sign != rhs.sign) return false;
        if (this->size() != rhs.size()) return false;
        for (int i = 0; i < this->size(); ++i) {
            if (this->data[i] != rhs.data[i]) return false;
        }
        return true;
    }

    bool operator<(const BigInt &rhs) const {
        if (sign != rhs.sign) return sign;
        return this->abs_less(rhs);
    }
    bool operator>(const BigInt &rhs) const { return rhs < *this; }
    bool operator<=(const BigInt &rhs) const { return !(*this > rhs); }
    bool operator>=(const BigInt &rhs) const { return !(*this < rhs); }

    friend std::istream &operator>>(std::istream &is, BigInt &rhs) {
        std::string s;
        is >> s;
        rhs = BigInt(s);
        return is;
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInt &rhs) {
        std::string s;
        for (auto i : rhs.data) s.push_back(char(i + '0'));
        if (rhs.sign) s.push_back('-');
        std::reverse(s.begin(), s.end());
        os << s;
        return os;
    }

    inline int size() const { return this->data.size(); }
    inline bool is_zero() const { return this->data.size() == 1 && this->data[0] == 0; }

    int back() const {
        assert(this->size() > 0);
        return this->data.back();
    }

    BigInt abs() const {
        if (!this->sign) return *this;
        return -(*this);
    }
    bool abs_less(const BigInt &rhs) const { return less(this->data, rhs.data); }

  private:
    std::vector<int> data;
    bool sign;

    static bool less(const std::vector<int> &a, const std::vector<int> &b) {
        if (a.size() != b.size()) return a.size() < b.size();
        for (int i = (int)a.size() - 1; i >= 0; --i) {
            if (a[i] != b[i]) return a[i] < b[i];
        }
        return false;
    }

    static void add(std::vector<int> &a, const std::vector<int> &b) {
        int n = std::max(a.size(), b.size());
        a.resize(n);
        for (int i = 0; i < (int)b.size(); ++i) a[i] += b[i];
        format(a);
    }
    static void sub(std::vector<int> &a, const std::vector<int> &b) {
        int n = std::max(a.size(), b.size());
        a.resize(n);
        for (int i = 0; i < (int)b.size(); ++i) a[i] -= b[i];
        format(a);
    }
    static void mul(std::vector<int> &a, const std::vector<int> &b) {
        a = convolution(a, b);
        format(a);
    }
    static void mul(std::vector<int> &data, int k) {
        std::for_each(data.begin(), data.end(), [k](auto &x) { x *= k; });
        format(data);
    }
    static void div(std::vector<int> &data, int k) {
        int x = 0;
        for (int i = (int)data.size() - 1; i >= 0; --i) {
            int r = (10 * x + data[i]) % k;
            data[i] = (10 * x + data[i]) / k;
            x = r;
        }
        format(data);
    }

    static void format(std::vector<int> &data) {
        for (int i = 0;; ++i) {
            if ((int)data.size() == i + 1) {
                if (std::abs(data[i]) <= 9) break;
                else data.emplace_back(0);
            }
            data[i + 1] += data[i] / 10;
            data[i] %= 10;
            if (data[i] < 0) --data[i + 1], data[i] += 10;
        }
        while ((int)data.size() > 1 && data.back() == 0) data.pop_back();
    }

    void format() {
        this->format(this->data);
        if (this->back() < 0) {
            this->inverse();
            this->format();
        }
        if (this->is_zero()) this->sign = false;
    }

    void inverse() {
        this->sign = !this->sign;
        std::for_each(this->data.begin(), this->data.end(), [](auto &x) { x = -x; });
    }

    int to_int() const { return this->sign ? -this->to_uint() : this->to_uint(); }
    unsigned int to_uint() const {
        int res = 0;
        for (int i = this->size() - 1; i >= 0; --i) res = res * 10 + this->data[i];
        return res;
    }
};
