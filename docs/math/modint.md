---
title: modint (static_modint / dynamic_modint)
documentation_of: //lib/math/modint.hpp
compile_example: true
---

整数を法 $m$ で正規化して保持し、加減乗除と累乗を通常の数値型に近い記法で扱う。
コンパイル時に法が決まる `static_modint` と、実行時に法を設定する `dynamic_modint` を提供する。

## 使い方

```cpp
#include "math/modint.hpp"

using Mint = modint998;  // static_modint<998244353>
Mint a = -2;
Mint b = 5;
Mint c = a * b + 3;
Mint d = b.pow(100);
unsigned int value = c.val();

using DynamicMint = dynamic_modint<0>;
DynamicMint::set_mod(1'000'000'007);
DynamicMint x = 123456789;
```

## API

| API | 内容 | 計算量 |
| --- | --- | --- |
| `template <class Derived> struct modint_common : modint_base` | static_modint と dynamic_modint が共有する公開演算<br>Derived は umod(), mul(), is_prime_mod() を提供する。 | 各演算の行に記載 |
| `constexpr unsigned int internal::val() const` | 保持している標準剰余を返す | $O(1)$ |
| `constexpr mint &operator++()` | 1を加算する | $O(1)$ |
| `constexpr mint &operator--()` | 1を減算する | $O(1)$ |
| `constexpr mint operator++(int)` | 1を加算する前の値を返す | $O(1)$ |
| `constexpr mint operator--(int)` | 1を減算する前の値を返す | $O(1)$ |
| `constexpr mint &operator+=(const mint &rhs)` | rhsを加算する | $O(1)$ |
| `constexpr mint &operator-=(const mint &rhs)` | rhsを減算する | $O(1)$ |
| `constexpr mint &operator*=(const mint &rhs)` | rhsを乗算する | $O(1)$ |
| `constexpr mint &operator/=(const mint &rhs)` | rhsで除算する | 素数法では法を $m$ として $O(\log m)$、動的法では $O(\log m)$ |
| `constexpr mint operator+() const` | 自身の値を返す | $O(1)$ |
| `constexpr mint operator-() const` | 加法逆元を返す | $O(1)$ |
| `constexpr mint internal::pow(std::int64_t n) const` | n乗を返す | $O(\log n)$ |
| `constexpr mint internal::inv() const` | 乗法逆元を返す | 法を $m$ として $O(\log m)$ |
| `friend constexpr mint operator+(const mint &lhs, const mint &rhs)` | 和を返す | $O(1)$ |
| `friend constexpr mint operator-(const mint &lhs, const mint &rhs)` | 差を返す | $O(1)$ |
| `friend constexpr mint operator*(const mint &lhs, const mint &rhs)` | 積を返す | $O(1)$ |
| `friend constexpr mint operator/(const mint &lhs, const mint &rhs)` | 商を返す | 法を $m$ として $O(\log m)$ |
| `friend constexpr bool operator==(const mint &lhs, const mint &rhs)` | 等しいか返す | $O(1)$ |
| `friend constexpr bool operator!=(const mint &lhs, const mint &rhs)` | 異なるか返す | $O(1)$ |
| `friend std::istream &operator>>(std::istream &is, mint &rhs)` | 整数を入力して法で正規化する | $O(1)$ |
| `friend std::ostream &operator<<(std::ostream &os, const mint &rhs)` | 標準剰余を出力する | $O(1)$ |
| `template <int m> requires(m >= 1) struct static_modint` | コンパイル時に法を固定する modint | 四則演算は $O(1)$、累乗と逆元は $O(\log m)$ |
| `using mint = static_modint;`<br>`using mint = dynamic_modint;` | この型自身 | 型エイリアスで実行時計算量はない |
| `using base = internal::modint_common<static_modint>;`<br>`using base = internal::modint_common<dynamic_modint>;` | 四則演算を実装する基底型 | 型エイリアスで実行時計算量はない |
| `using base::_v;` | 基底型が保持する正規化済みの値 | $O(1)$ で参照可能 |
| `static constexpr unsigned int umod()`<br>`static unsigned int umod()` | 法を unsigned int で返す | $O(1)$ |
| `static constexpr bool is_prime_mod()` | 法が素数かをコンパイル時に返す | コンパイル時定数で実行時計算量はない |
| `static constexpr unsigned int mul(unsigned int a, unsigned int b)` | aとbを乗算して法mで剰余を取る | $O(1)$ |
| `static constexpr int mod()` | 法を返す | $O(1)$ |
| `static constexpr mint raw(int v)`<br>`static mint raw(int v)` | 正規化済みの値vから検査なしで構築する | $O(1)$ |
| `constexpr static_modint() = default;` | 0を構築する | $O(1)$ |
| `template <std::integral T> constexpr static_modint(T v)` | 符号付き整数を法mで正規化して構築する | $O(1)$ |
| `template <std::unsigned_integral T> constexpr static_modint(T v)` | 符号なし整数を法mで正規化して構築する | $O(1)$ |
| `template <int id> struct dynamic_modint : internal::modint_common<dynamic_modint<id>>` | 実行時に法を設定する modint | 四則演算は $O(1)$、累乗と逆元は法を $m$ として $O(\log m)$ |
| `static bool is_prime_mod()` | 法を素数として扱うか返す | $O(1)$ |
| `static unsigned int mul(unsigned int a, unsigned int b)` | aとbをBarrett reductionで乗算する | $O(1)$ |
| `static int mod()` | 現在の法を返す | $O(1)$ |
| `static void set_mod(int m)` | このidの法をmへ設定する | $O(1)$ |
| `dynamic_modint() = default;` | 0を構築する | $O(1)$ |
| `template <std::integral T> dynamic_modint(T v)` | 符号付き整数を現在の法で正規化して構築する | $O(1)$ |
| `template <std::unsigned_integral T> dynamic_modint(T v)` | 符号なし整数を現在の法で正規化して構築する | $O(1)$ |
| `using modint998 = static_modint<998244353>;` | 法998244353のstatic_modint | 型エイリアスで実行時計算量はない |
| `using modint107 = static_modint<1000000007>;` | 法1000000007のstatic_modint | 型エイリアスで実行時計算量はない |
| `using modint = dynamic_modint<-1>;` | 既定id -1のdynamic_modint | 型エイリアスで実行時計算量はない |

## 補足

- 除算には除数と法が互いに素であることが必要。素数法では除数が0でないこと。
  条件を満たさない場合は `assert` に失敗する。
- `static_modint` は法が素数かをコンパイル時に判定し、逆元を
  $a^{m-2}$ で求める。合成数法では拡張 Euclid 法を使う。
- `dynamic_modint<id>` の法は同じ `id` の全インスタンスで共有される。異なる法を同時に
  使う場合は異なる `id` を指定する。
- `raw(value)` は `0 <= value < mod()` を呼び出し側が保証できる場合だけ使う。
- `pow` の指数は非負。負の指数は `x.inv().pow(-n)` として明示する。

## 検証

- [AOJ NTL_1_B Power](https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_B)
- [AOJ 0264 Finite Field Calculator](https://onlinejudge.u-aizu.ac.jp/problems/0264)
- [Point Set Range Composite](https://judge.yosupo.jp/problem/point_set_range_composite)
- [Convolution](https://judge.yosupo.jp/problem/convolution_mod)
