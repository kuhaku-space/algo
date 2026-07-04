#pragma once
#include <cctype>
#include <stdexcept>
#include <string>
#include <string_view>

/// @brief 四則演算の再帰下降パーサ
/// @details 文法:
///   expr    = term { ('+' | '-') term }
///   term    = factor { ('*' | '/') factor }
///   factor  = ('+' | '-') factor | primary
///   primary = number | '(' expr ')'
/// 値型 @c T は算術演算 (@c + @c - @c * @c /) を持てば何でもよい
/// (@c long @c long のほか @c modint 等でも動く)。空白は無視する。
template <class T = long long>
struct ExprParser {
    explicit ExprParser(std::string_view s) : s(s), pos(0) {}

    /// @brief 式全体を評価する (末尾に余分な文字が残ればエラー)
    T parse() {
        T res = expr();
        skip_space();
        if (pos != s.size()) throw std::runtime_error("ExprParser: unexpected trailing character");
        return res;
    }

  private:
    std::string_view s;
    std::size_t pos;

    void skip_space() {
        while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos]))) ++pos;
    }

    // 現在位置の文字を覗き見る (末尾なら '\0')
    char peek() {
        skip_space();
        return pos < s.size() ? s[pos] : '\0';
    }

    T expr() {
        T res = term();
        for (;;) {
            char c = peek();
            if (c == '+') {
                ++pos;
                res += term();
            } else if (c == '-') {
                ++pos;
                res -= term();
            } else {
                return res;
            }
        }
    }

    T term() {
        T res = factor();
        for (;;) {
            char c = peek();
            if (c == '*') {
                ++pos;
                res *= factor();
            } else if (c == '/') {
                ++pos;
                res /= factor();
            } else {
                return res;
            }
        }
    }

    T factor() {
        char c = peek();
        if (c == '+') {
            ++pos;
            return +factor();
        }
        if (c == '-') {
            ++pos;
            return -factor();
        }
        return primary();
    }

    T primary() {
        char c = peek();
        if (c == '(') {
            ++pos;
            T res = expr();
            if (peek() != ')') throw std::runtime_error("ExprParser: expected ')'");
            ++pos;
            return res;
        }
        return number();
    }

    T number() {
        skip_space();
        std::size_t start = pos;
        T res = T(0);
        while (pos < s.size() && std::isdigit(static_cast<unsigned char>(s[pos]))) {
            res = res * T(10) + T(s[pos] - '0');
            ++pos;
        }
        if (pos == start) throw std::runtime_error("ExprParser: expected number");
        return res;
    }
};

/// @brief 四則演算の式文字列を評価する
template <class T = long long>
T eval_expr(std::string_view s) {
    return ExprParser<T>(s).parse();
}
