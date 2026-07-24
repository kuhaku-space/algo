#pragma once
#include <cctype>
#include <functional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

/// @brief 汎用式パーサ (演算子優先順位法 / precedence climbing)
/// @details 二項演算子・前置単項演算子・原子(アトム)読み取りを差し替えて
///   任意の式文法を構築できる。値型 @c T は「意味」を表し、演算子・アトムの
///   コールバックが返す。@c T を数値型にすれば評価器、AST ノードにすれば
///   構文木を組み立てるパーサになる。
///
///   - @c binary(op, prec, assoc, f): 二項演算子。@c prec が大きいほど優先。
///   - @c prefix(op, f): 前置単項演算子。二項演算子より強く結合する。
///   - @c atom(f): 数値・変数・関数呼び出し等の最小単位を読む。
///     コールバックは @c *this を受け取り、@c parse_expression() で
///     部分式を再帰的に読める(関数の引数や括弧内など)。
///   - @c group(open, close): 明示的なグループ化括弧(既定は @c () )。
///
///   演算子トークンは多文字可(最長一致)。空白は無視する。
/// @complexity 入力長を $n$、登録演算子数を $A$ として解析は $O(nA)$（callbackの計算量を除く）
template <class T>
struct ExpressionParser {
    /// @brief 結合性
    /// @complexity 列挙型で実行時計算量はない
    enum class Assoc { Left, Right };

    /// @brief 二項演算callback型
    /// @complexity 型エイリアスで実行時計算量はない
    using binary_fn = std::function<T(const T &, const T &)>;

    /// @brief 単項演算callback型
    /// @complexity 型エイリアスで実行時計算量はない
    using unary_fn = std::function<T(const T &)>;

    /// @brief アトム読取りcallback型
    /// @complexity 型エイリアスで実行時計算量はない
    using atom_fn = std::function<T(ExpressionParser &)>;
    /// @brief 二項演算子ガード: トークン直後の残り入力を見て演算子として
    ///   適用してよいか判定する。閉じ記号と演算子が文字レベルで衝突する
    ///   文脈依存文法 (例: AOJ 2570 の @c ">>" と @c ">") に使う。
    /// @complexity 型エイリアスで実行時計算量はない
    using guard_fn = std::function<bool(std::string_view)>;

    /// @brief 二項演算子を登録する (fluent)
    /// @complexity トークン長を $L$ として償却 $O(L)$
    ExpressionParser &binary(std::string op, int prec, Assoc assoc, binary_fn f) {
        binops.push_back({std::move(op), prec, assoc, std::move(f), nullptr});
        return *this;
    }
    /// @brief ガード付き二項演算子を登録する (fluent)
    /// @details @c guard(after) が @c false のときは、その位置の一致を演算子と
    ///   みなさない (トークンは消費されず、閉じ記号等として残る)。
    ///   @c after はトークン直後の残り入力。
    /// @complexity トークン長を $L$ として償却 $O(L)$
    ExpressionParser &binary(std::string op, int prec, Assoc assoc, binary_fn f, guard_fn guard) {
        binops.push_back({std::move(op), prec, assoc, std::move(f), std::move(guard)});
        return *this;
    }
    /// @brief 暗黙の連接 (演算子記号なしで項が並ぶ) を登録する (fluent)
    /// @details 空トークンの二項演算子として扱う。項が続くかどうかを表す
    ///   @c guard は必須 (無いと停止できず無限ループになる)。@c guard(rest)
    ///   が @c true のときだけ次の項を連接する。文字列連接・関数適用など。
    /// @complexity 償却 $O(1)$
    ExpressionParser &concat(int prec, Assoc assoc, binary_fn f, guard_fn guard) {
        binops.push_back({std::string(), prec, assoc, std::move(f), std::move(guard)});
        return *this;
    }
    /// @brief 前置単項演算子を登録する (fluent)
    /// @complexity トークン長を $L$ として償却 $O(L)$
    ExpressionParser &prefix(std::string op, unary_fn f) {
        unops.push_back({std::move(op), std::move(f)});
        return *this;
    }
    /// @brief アトム読み取りコールバックを設定する (fluent)
    /// @complexity $O(1)$
    ExpressionParser &atom(atom_fn f) {
        atom_reader = std::move(f);
        return *this;
    }
    /// @brief グループ化括弧を設定する (fluent)
    /// @complexity $O(1)$
    ExpressionParser &group(char open, char close) {
        lp = open, rp = close, has_group = true;
        return *this;
    }
    /// @brief 組み込みのグループ化括弧を無効化する (fluent)
    /// @details 括弧を atom 側で自前処理したいとき (例: 分子式 @c "(X)2" の
    ///   ように閉じ括弧の直後に処理を続けたいとき) に使う。
    /// @complexity $O(1)$
    ExpressionParser &no_group() {
        has_group = false;
        return *this;
    }

    /// @brief 式全体を解析する (末尾に余分な文字が残ればエラー)
    /// @complexity 入力長を $n$、登録演算子数を $A$ として $O(nA)$
    T parse(std::string_view str) {
        owned.assign(str.data(), str.size());  // std::string 末尾の '\0' を番兵に使う
        s = owned, pos = 0;
        T res = parse_expression(0);
        skip_space();
        if (pos != s.size()) throw std::runtime_error("ExpressionParser: unexpected trailing character");
        return res;
    }

    // ---- アトムコールバックから使う低レベル API ----

    /// @brief 優先順位 @c min_prec 以上の部分式を解析する
    /// @complexity 読み取る長さを $n$、登録演算子数を $A$ として $O(nA)$
    T parse_expression(int min_prec = 0) {
        T lhs = parse_prefix();
        for (;;) {
            const BinOp *op = peek_binary();
            if (!op || op->prec < min_prec) return lhs;
            pos += op->token.size();
            int next_min = op->assoc == Assoc::Left ? op->prec + 1 : op->prec;
            T rhs = parse_expression(next_min);
            lhs = op->f(lhs, rhs);
        }
    }

    /// @brief 空白を読み飛ばした現在の文字 (末尾なら @c '\0')
    /// @complexity 読み飛ばす空白数を $k$ として $O(k)$
    char peek() {
        skip_space();
        return cur();
    }
    /// @brief 空白を読み飛ばさない現在位置の文字 (末尾なら @c '\0')
    /// @details 番兵 (@c std::string 末尾の @c '\0') により末尾でも安全に
    ///   @c '\0' を返す。アトム側で @c rest().size() の範囲チェックをせず
    ///   @c cur() と @c advance() で1文字ずつ走査できる。
    /// @complexity $O(1)$
    char cur() const { return s.data()[pos]; }
    /// @brief 残りの入力
    /// @complexity $O(1)$
    std::string_view rest() const { return s.substr(pos); }
    /// @brief トークン @c tok が現在位置に一致すれば消費して @c true
    /// @complexity 読み飛ばす空白とトークン長を合わせて $O(k)$
    bool consume(std::string_view tok) {
        skip_space();
        if (s.substr(pos).starts_with(tok)) {
            pos += tok.size();
            return true;
        }
        return false;
    }
    /// @brief 現在位置を @c n 文字進める
    /// @complexity $O(1)$
    void advance(std::size_t n = 1) { pos += n; }
    /// @brief 非負整数を @c long @c long として読む (@c T に依らない。AST 構築等で有用)
    /// @complexity 読み取る文字数を $k$ として $O(k)$
    long long read_uint() {
        skip_space();
        std::size_t start = pos;
        long long res = 0;
        while (std::isdigit(static_cast<unsigned char>(cur()))) res = res * 10 + (s[pos++] - '0');
        if (pos == start) throw std::runtime_error("ExpressionParser: expected number");
        return res;
    }
    /// @brief 英字からなる識別子を読む (先頭が英字でなければ空文字列)
    /// @complexity 読み取る文字数を $k$ として $O(k)$
    std::string_view read_identifier() {
        skip_space();
        std::size_t start = pos;
        while (std::isalpha(static_cast<unsigned char>(cur()))) ++pos;
        return s.substr(start, pos - start);
    }

    /// @brief 非負整数を読む既定アトム (@c T が整数から構築可能なとき利用可能)
    /// @complexity 読み取る文字数を $k$ として $O(k)$
    static T integer_atom(ExpressionParser &p) {
        p.skip_space();
        std::size_t start = p.pos;
        T res = T(0);
        while (std::isdigit(static_cast<unsigned char>(p.cur()))) {
            res = res * T(10) + T(p.cur() - '0');
            ++p.pos;
        }
        if (p.pos == start) throw std::runtime_error("ExpressionParser: expected number");
        return res;
    }

  private:
    struct BinOp {
        std::string token;
        int prec;
        Assoc assoc;
        binary_fn f;
        guard_fn guard;
    };
    struct UnOp {
        std::string token;
        unary_fn f;
    };

    std::vector<BinOp> binops;
    std::vector<UnOp> unops;
    atom_fn atom_reader;
    char lp = '(', rp = ')';
    bool has_group = true;
    std::string owned;   // 入力の実体。std::string は末尾 '\0' を保証するので番兵になる
    std::string_view s;  // owned 上のビュー (実長。番兵 '\0' は含まない)
    std::size_t pos = 0;

    void skip_space() {
        while (std::isspace(static_cast<unsigned char>(cur()))) ++pos;
    }

    // 現在位置に一致する二項演算子のうち最長のものを消費せず返す
    const BinOp *peek_binary() {
        skip_space();
        std::string_view r = s.substr(pos);
        const BinOp *best = nullptr;
        for (const BinOp &op : binops) {
            if (!r.starts_with(op.token)) continue;
            if (op.guard && !op.guard(r.substr(op.token.size()))) continue;
            if (!best || op.token.size() > best->token.size()) best = &op;
        }
        return best;
    }

    T parse_prefix() {
        skip_space();
        std::string_view r = s.substr(pos);
        const UnOp *best = nullptr;
        for (const UnOp &op : unops) {
            if (r.starts_with(op.token) && (!best || op.token.size() > best->token.size())) best = &op;
        }
        if (best) {
            pos += best->token.size();
            return best->f(parse_prefix());
        }
        return parse_atom();
    }

    T parse_atom() {
        if (has_group && peek() == lp) {
            ++pos;
            T res = parse_expression(0);
            if (peek() != rp) throw std::runtime_error("ExpressionParser: expected closing bracket");
            ++pos;
            return res;
        }
        if (!atom_reader) throw std::runtime_error("ExpressionParser: no atom reader configured");
        return atom_reader(*this);
    }
};

/// @brief 標準的な四則演算パーサを構築する
/// @details @c + @c - @c * @c / ・単項 @c ± ・括弧・非負整数リテラルに対応。
///   値型 @c T は算術演算を持てば何でもよい (@c long @c long ・@c modint 等)。
/// @complexity $O(1)$
template <class T = long long>
ExpressionParser<T> arithmetic_parser() {
    using P = ExpressionParser<T>;
    P p;
    p.prefix("-", std::negate<T>())
        .prefix("+", [](const T &x) { return +x; })
        .binary("+", 10, P::Assoc::Left, std::plus<T>())
        .binary("-", 10, P::Assoc::Left, std::minus<T>())
        .binary("*", 20, P::Assoc::Left, std::multiplies<T>())
        .binary("/", 20, P::Assoc::Left, std::divides<T>())
        .atom(P::integer_atom);
    return p;
}

/// @brief 四則演算の式文字列を評価する
/// @complexity 入力長を $n$ として $O(n)$
template <class T = long long>
T eval_expr(std::string_view s) {
    return arithmetic_parser<T>().parse(s);
}
