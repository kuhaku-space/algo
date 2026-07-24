---
title: NTT・畳み込み (convolution)
documentation_of: //lib/convolution/ntt.hpp
compile_example: true
---

Number Theoretic Transform (NTT) により、多項式の係数列の畳み込みを
$O(n\log n)$ で計算する。NTT-friendly な法に加え、3素数と Garner 法を使った
64 bit整数畳み込み・任意mod畳み込みも提供する。

短い入力は自動的に愚直畳み込みへ切り替わる。

## 使い方

```cpp
#include "convolution/ntt.hpp"

std::vector<modint998> a = {1, 2, 3};
std::vector<modint998> b = {4, 5};
auto c = convolution(a, b);  // {4, 13, 22, 15}

std::vector<int> x = {1, 2, 3};
std::vector<int> y = {4, 5};
auto arbitrary_mod = convolution_mod<1'000'000'007>(x, y);
```

## API

$N = |a| + |b| - 1$ とする。空の入力がある場合、畳み込みは空列を返す。

| API | 内容 | 主な前提 | 計算量 |
| --- | --- | --- | --- |
| `convolution(a, b)` | static modint係数の畳み込み | 変換長が `mod - 1` を割り切る | $O(N\log N)$ |
| `convolution<mod>(a, b)` | 整数入力を `mod` で畳み込み | `mod` は NTT-friendly | $O(N\log N)$ |
| `convolution_square(a)` | `a * a` 専用の高速版 | NTT-friendly | $O(N\log N)$ |
| `middle_product(a, b)` | `c[i] = sum_j a[i+j] b[j]` | `b.size() <= a.size()` | $O(n\log n)$ |
| `convolution_ll(a, b)` | 3素数から符号付き64 bit係数を復元 | 真値が `int64_t` に収まる | $O(N\log N)$ |
| `convolution_ll2(a, b)` | 2素数で高速に整数係数を復元 | 非負係数かつ真値 $< M_1M_3$ | $O(N\log N)$ |
| `convolution_mod<mod>(a, b)` | 任意の法で畳み込み | 入力係数は `[0, mod)` | $O(N\log N)$ |

## 補足

- NTT版では `bit_ceil(N)` が `mod - 1` を割り切る必要がある。既定の998244353では
  $2^{23}$ までの変換が可能。
- `convolution_ll`、`convolution_ll2`、`convolution_mod` の出力長は $2^{24}$ 以下。
- 同じ列同士の `convolution(a, a)` は自動検出されるが、`convolution_square(a)` なら
  比較を省略して意図を明示できる。
- `convolution_ll2` は係数が非負で、各出力係数が
  $754974721 \times 469762049$ 未満である場合だけ正しく復元できる。
- `convolution_mod` は入力を法で正規化しない。負値や `mod` 以上の値を含む場合は
  `convolution_ll` などで真の整数畳み込みを求めてから剰余を取る。

## 検証

- [Convolution](https://judge.yosupo.jp/problem/convolution_mod)
- [Convolution Mod 1,000,000,007](https://judge.yosupo.jp/problem/convolution_mod_1000000007)
- [Product of Polynomial Sequence](https://judge.yosupo.jp/problem/product_of_polynomial_sequence)
