#include "template/template.hpp"

/**
 * @brief 分数ライブラリ
 * 
 */
struct Fraction {
    int64_t x, y;

    Fraction() : x(0), y(1) {}

    Fraction(int64_t _x, int64_t _y = 1) : x(_x), y(_y) { this->common(); }

    int64_t gcd(int64_t a, int64_t b) const {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    Fraction &operator+=(const Fraction &rhs) {
        x = x * rhs.y + y * rhs.x;
        y *= rhs.y;
        this->common();
        return *this;
    }
    Fraction &operator-=(const Fraction &rhs) {
        x = x * rhs.y - y * rhs.x;
        y *= rhs.y;
        this->common();
        return *this;
    }
    Fraction &operator*=(const Fraction &rhs) {
        x *= rhs.x, y *= rhs.y;
        this->common();
        return *this;
    }
    Fraction &operator/=(const Fraction &rhs) {
        x *= rhs.y, y *= rhs.x;
        this->common();
        return *this;
    }

    Fraction &operator++() {
        this->x += this->y;
        return *this;
    }
    Fraction operator++(int) {
        Fraction tmp(*this);
        this->operator++();
        return tmp;
    }
    Fraction &operator--() {
        this->x -= this->y;
        return *this;
    }
    Fraction operator--(int) {
        Fraction tmp(*this);
        this->operator--();
        return tmp;
    }

    Fraction operator-() const { return Fraction(-x, y); }

    Fraction operator+(const Fraction &rhs) const { return Fraction(*this) += rhs; }
    Fraction operator-(const Fraction &rhs) const { return Fraction(*this) -= rhs; }
    Fraction operator*(const Fraction &rhs) const { return Fraction(*this) *= rhs; }
    Fraction operator/(const Fraction &rhs) const { return Fraction(*this) /= rhs; }

    bool operator==(const Fraction &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(const Fraction &rhs) const { return x != rhs.x || y != rhs.y; }
    bool operator<(const Fraction &rhs) const { return x * rhs.y < rhs.x * y; }
    bool operator>(const Fraction &rhs) const { return x * rhs.y > rhs.x * y; }

    friend ostream &operator<<(ostream &os, const Fraction &rhs) { return os << rhs.to_double(); }

    friend istream &operator>>(istream &is, Fraction &a) {
        string s;
        is >> s;
        bool f = false;
        int64_t x = 0, y = 1;
        for (auto c : s) {
            if (c == '.') {
                f = true;
                continue;
            }

            x *= 10, x += c - '0';
            if (f) y *= 10;
        }
        a = Fraction(x, y);
        return is;
    }

    double to_double() const { return (double)x / y; }

  private:
    void common() {
        int64_t g = gcd(x, y);
        if (g) x /= g, y /= g;
        if (y < 0) x *= -1, y *= -1;
    }
};
