#pragma once
#include <locale>
#include <string>
#include <vector>

/// @brief 文字または文字列を整数列へ変換する
/// @details 文字種の先頭または指定したアルファベット内の位置を整数値として返す。
/// @complexity 文字種による1文字変換は $O(1)$、指定文字列による変換は
/// アルファベット長を $\sigma$ として $O(\sigma)$。列全体は要素数倍
struct string_converter {
    /// @brief 文字種の先頭文字を返す
    /// @complexity $O(1)$
    char type(const char &c) const {
        return (std::islower(c) ? 'a' : std::isupper(c) ? 'A' : std::isdigit(c) ? '0' : 0);
    }

    /// @brief 文字を現在の文字種内の位置へ変換する
    /// @complexity $O(1)$
    int convert(const char &c) {
        if (!start) start = type(c);
        return c - start;
    }

    /// @brief 文字を指定alphabet内の位置へ変換する
    /// @complexity alphabet長を $\sigma$ として $O(\sigma)$
    int convert(const char &c, const std::string &chars) { return chars.find(c); }

    /// @brief containerを文字種内の位置列へ変換する
    /// @complexity 要素数を $n$ として $O(n)$
    template <class T>
    auto convert(const T &v) {
        std::vector<decltype(convert(v[0]))> res;
        res.reserve(v.size());
        for (auto &&e : v) res.emplace_back(convert(e));
        return res;
    }

    /// @brief containerを指定alphabet内の位置列へ変換する
    /// @complexity 要素数を $n$、alphabet長を $\sigma$ として $O(n\sigma)$
    template <class T>
    auto convert(const T &v, const std::string &chars) {
        std::vector<decltype(convert(v[0], chars))> res;
        res.reserve(v.size());
        for (auto &&e : v) res.emplace_back(convert(e, chars));
        return res;
    }

    /// @brief 文字を文字種または起点sからの位置へ変換する
    /// @complexity $O(1)$
    int operator()(const char &v, char s = 0) {
        start = s;
        return convert(v);
    }

    /// @brief 文字を指定alphabet内の位置へ変換する
    /// @complexity alphabet長を $\sigma$ として $O(\sigma)$
    int operator()(const char &v, const std::string &chars) { return convert(v, chars); }

    /// @brief containerを文字種または起点sからの位置列へ変換する
    /// @complexity 要素数を $n$ として $O(n)$
    template <class T>
    auto operator()(const T &v, char s = 0) {
        start = s;
        return convert(v);
    }

    /// @brief containerを指定alphabet内の位置列へ変換する
    /// @complexity 要素数を $n$、alphabet長を $\sigma$ として $O(n\sigma)$
    template <class T>
    auto operator()(const T &v, const std::string &chars) {
        return convert(v, chars);
    }

  private:
    char start = 0;
} to_int;
