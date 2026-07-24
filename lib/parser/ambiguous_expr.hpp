#pragma once
#include <cctype>
#include <cstddef>
#include <functional>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

/// @brief 曖昧な二項演算式の「全評価順序で得られる値の集合」
/// @details すべての演算子は二項で、任意の結合順序 (全 parenthesization) を許す。
///   入力中の括弧 @c () は固定のグループ化として扱い、その内側も再帰的に
///   全順序を試す。@c op(c, f) で演算子を登録する。@c f は無効な演算
///   (0 除算など) に対し @c std::nullopt を返すとその経路を捨てる。
///   値の集合を返すので、@c size() で「あり得る結果の通り数」が得られる
///   (AOJ 2255 など)。オペランド数を @c k とすると区間DPで
///   @c O(k^2) 個の部分区間 × 集合サイズの二乗で評価する。
/// @complexity オペランド数を $k$、各区間の値集合の最大サイズを $S$ として $O(k^3S^2\log S)$
template <class T = long long>
struct AmbiguousExpr {
    /// @brief 二項演算を表す関数型
    /// @complexity 型エイリアスで実行時計算量はない
    using combine_fn = std::function<std::optional<T>(const T &, const T &)>;

    /// @brief 二項演算子を登録する (fluent)
    /// @complexity $O(\log A)$（$A$ は登録済み演算子数）
    AmbiguousExpr &op(char c, combine_fn f) {
        ops[c] = std::move(f);
        return *this;
    }

    /// @brief 式全体をすべての評価順序で評価し、得られる値の集合を返す
    /// @complexity オペランド数を $k$、値集合の最大サイズを $S$ として $O(k^3S^2\log S)$
    std::set<T> values(std::string_view str) {
        owned.assign(str.data(), str.size());  // std::string 末尾の '\0' を番兵に使う
        s = owned, pos = 0;
        std::set<T> res = parse_sequence();
        skip_space();
        if (pos != s.size()) throw std::runtime_error("AmbiguousExpr: unexpected trailing character");
        return res;
    }

  private:
    std::map<char, combine_fn> ops;
    std::string owned;   // 入力の実体。std::string は末尾 '\0' を保証するので番兵になる
    std::string_view s;  // owned 上のビュー (実長。番兵 '\0' は含まない)
    std::size_t pos = 0;

    // 現在位置の文字。番兵により pos == s.size() でも '\0' を安全に返せるので、
    // 文字走査で pos < s.size() の範囲比較が不要になる (pos は常に s.size() 以下)。
    char cur() const { return s.data()[pos]; }

    void skip_space() {
        while (std::isspace(static_cast<unsigned char>(cur()))) ++pos;
    }
    char peek() {
        skip_space();
        return cur();
    }

    // オペランド = 非負整数 | '(' 列 ')' 。集合を返す。
    std::set<T> parse_operand() {
        if (peek() == '(') {
            ++pos;
            std::set<T> res = parse_sequence();
            if (peek() != ')') throw std::runtime_error("AmbiguousExpr: expected ')'");
            ++pos;
            return res;
        }
        skip_space();
        std::size_t start = pos;
        T v = T(0);
        while (std::isdigit(static_cast<unsigned char>(cur()))) v = v * T(10) + T(s[pos++] - '0');
        if (pos == start) throw std::runtime_error("AmbiguousExpr: expected number");
        return {v};
    }

    // 列 = オペランド (演算子 オペランド)* を全結合順序で評価
    std::set<T> parse_sequence() {
        std::vector<std::set<T>> operand{parse_operand()};
        std::vector<char> op_seq;
        for (char c = peek(); ops.count(c); c = peek()) {
            ++pos;
            op_seq.push_back(c);
            operand.push_back(parse_operand());
        }
        int n = operand.size();
        // dp[i][j] = オペランド i..j から得られる値集合
        std::vector<std::vector<std::set<T>>> dp(n, std::vector<std::set<T>>(n));
        for (int i = 0; i < n; ++i) dp[i][i] = operand[i];
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                for (int k = i; k < j; ++k) {
                    const combine_fn &f = ops.at(op_seq[k]);
                    for (const T &a : dp[i][k])
                        for (const T &b : dp[k + 1][j])
                            if (std::optional<T> r = f(a, b)) dp[i][j].insert(*r);
                }
            }
        }
        return dp[0][n - 1];
    }
};
