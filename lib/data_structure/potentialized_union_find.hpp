#pragma once
#include <concepts>
#include <utility>
#include <vector>

namespace internal {

/// @brief 加法的に書かれた可換群か（合成 `+`・逆元 単項 `-`・単位元 `T(0)`）
/// @details `int` や modint など `+`/`-` を持つ型はこちらで扱う。
///          modint のように `*`/`inv()` も持つ環型でも、ポテンシャル差は加法とみなす
///          （`T(0)` を単位元とする）ため加法群を優先する。
template <class T>
concept additive_group = requires(const T &a) {
    T(0);
    { a + a } -> std::convertible_to<T>;
    { -a } -> std::convertible_to<T>;
};

/// @brief 乗法的に書かれた群か（合成 `*`・逆元 `.inv()`・単位元 `T()`）
/// @details 非可換群（行列など）もこちらで扱う。`+`/`-` を持つ加法群は @ref additive_group を
///          優先するため除外する（環型を誤って乗法群と判定しないため）。
template <class T>
concept multiplicative_group = !additive_group<T> && requires(const T &a) {
    T();
    { a * a } -> std::convertible_to<T>;
    { a.inv() } -> std::convertible_to<T>;
};

/// @brief 群 T の単位元
template <multiplicative_group T>
T group_identity() {
    return T();
}
template <additive_group T>
T group_identity() {
    return T(0);
}

/// @brief 群 T の二項演算 a・b
template <multiplicative_group T>
T group_op(const T &a, const T &b) {
    return a * b;
}
template <additive_group T>
T group_op(const T &a, const T &b) {
    return a + b;
}

/// @brief 群 T の逆元 a^{-1}
template <multiplicative_group T>
T group_inv(const T &a) {
    return a.inv();
}
template <additive_group T>
T group_inv(const T &a) {
    return -a;
}

/// @brief @ref potentialized_union_find が扱える群
template <class T>
concept group = multiplicative_group<T> || additive_group<T>;

}  // namespace internal

/// @brief ポテンシャル付き素集合データ構造（可換・非可換どちらの群でも可）
/// @details 各要素 x に群 G の隠れた値 a[x] が割り当てられているとし、
///          a[x]^{-1} ・ a[y] という相対関係（ポテンシャル差）を管理する。
///          G が `*` と `.inv()` を持てば乗法群（非可換も可・単位元は `G()`）、
///          `+` と単項 `-` を持てば加法可換群（単位元は `G(0)`）として自動的に扱う。
/// @tparam G 群を表す型
template <internal::group G>
struct potentialized_union_find {
    potentialized_union_find() = default;
    explicit potentialized_union_find(int n) : _data(n, -1), _pot(n, internal::group_identity<G>()) {}

    /// @brief x の根を返す（経路圧縮あり）。同時に _pot[x] を根に対する相対値へ更新する。
    int root(int x) {
        if (_data[x] < 0) return x;
        int r = root(_data[x]);
        _pot[x] = internal::group_op(_pot[_data[x]], _pot[x]);
        return _data[x] = r;
    }
    int get_root(int x) { return root(x); }

    bool is_root(int x) const { return _data[x] < 0; }

    /// @brief 根に対する相対ポテンシャル a[root]^{-1} ・ a[x] を返す。
    G potential(int x) {
        root(x);
        return _pot[x];
    }
    G get_potential(int x) { return potential(x); }

    bool same(int x, int y) { return root(x) == root(y); }
    bool is_same(int x, int y) { return same(x, y); }

    int size(int x) { return -_data[root(x)]; }
    int get_size(int x) { return size(x); }

    /// @brief a[x]^{-1} ・ a[y] を返す（x, y は同一集合に属していること）。
    G diff(int x, int y) { return internal::group_op(internal::group_inv(potential(x)), potential(y)); }
    G get_diff(int x, int y) { return diff(x, y); }

    /// @brief 関係 a[x]^{-1} ・ a[y] = w を追加する。
    /// @return 集合が新たに併合されたら true、既に同一集合なら false。
    /// @note 戻り値が false でも矛盾検出はしない。整合性確認は @ref valid を使う。
    bool unite(int x, int y, const G &w) {
        G px = potential(x), py = potential(y);
        x = root(x), y = root(y);
        if (x == y) return false;
        // a[x]^{-1} ・ a[y] = px ・ pot ・ py^{-1} = w  =>  pot(x->y) = px ・ w ・ py^{-1}
        G pot = internal::group_op(internal::group_op(px, w), internal::group_inv(py));
        if (_data[x] > _data[y]) {
            std::swap(x, y);
            pot = internal::group_inv(pot);  // pot(y->x) = (a[x]^{-1} ・ a[y])^{-1}
        }
        _data[x] += _data[y];
        _data[y] = x;
        _pot[y] = pot;
        return true;
    }

    /// @brief 関係 a[x]^{-1} ・ a[y] = w が既存の情報と整合するか確認する。
    /// @details 別集合なら併合して true、同一集合なら現在の差と一致するかを返す。
    bool valid(int x, int y, const G &w) {
        if (same(x, y)) return diff(x, y) == w;
        return unite(x, y, w);
    }

  private:
    std::vector<int> _data;
    std::vector<G> _pot;
};
