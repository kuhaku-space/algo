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

| API | 内容 | 計算量 |
| --- | --- | --- |
| `static constexpr int CONVOLUTION_NAIVE_THRESHOLD = 60;` | 愚直畳み込みへ切り替える入力サイズの閾値 | コンパイル時定数で実行時計算量はない |
| `template <internal::static_modint_c mint> std::vector<mint> convolution(const std::vector<mint> &a, const std::vector<mint> &b)` | NTT による畳み込み (modint 版)<br>**テンプレート引数:** `mint`: NTT-friendly な static modint (mod - 1 が畳み込み長で割り切れること)<br>**引数:** `a`: 入力多項式の係数列、`b`: 入力多項式の係数列<br>**戻り値:** std::vector<mint> a と b の畳み込み (長さ a.size() + b.size() - 1) | 出力長を $N$ として $O(N\log N)$ |
| `template <internal::static_modint_c mint> std::vector<mint> convolution_square(const std::vector<mint> &a)` | 自乗畳み込み (a と a の畳み込み, modint 版)<br>a を自身と畳み込む。順変換を 1 回に削減できるため convolution(a, a) より速い。<br>**テンプレート引数:** `mint`: NTT-friendly な static modint<br>**引数:** `a`: 入力多項式の係数列<br>**戻り値:** std::vector<mint> a と a の畳み込み (長さ 2 * a.size() - 1)<br>**参考:** [https://noshi91.hatenablog.com/entry/2023/12/10/163348](https://noshi91.hatenablog.com/entry/2023/12/10/163348) | 出力長を $N$ として $O(N\log N)$ |
| `template <unsigned int mod = 998244353, std::integral T> std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b)` | NTT による畳み込み (整数版)<br>**テンプレート引数:** `mod`: NTT-friendly な素数 mod (既定: 998244353)、`T`: 整数型 (std::integral)<br>**引数:** `a`: 入力多項式の係数列、`b`: 入力多項式の係数列<br>**戻り値:** std::vector<T> a と b の畳み込みを mod で取った値 (長さ a.size() + b.size() - 1)<br>**備考:** 各係数は modint コンストラクタを通して mod で正規化される (負値も可)。 | 出力長を $N$ として $O(N\log N)$ |
| `template <internal::static_modint_c mint> std::vector<mint> middle_product(const std::vector<mint> &a, const std::vector<mint> &b)` | middle product / 転置乗算 (modint 版)<br>a (長さ n) と b (長さ m, m <= n) に対し c[i] = sum_j a[i+j] * b[j] (i = 0 .. n-m) を返す (長さ n-m+1)。a と rev(b) のフル積の中央部に等しく、 変換長が bit_ceil(n) で済む。多項式補間・分割統治など「ずらし内積」が要る場面で使う。<br>**テンプレート引数:** `mint`: NTT-friendly な static modint<br>**引数:** `a`: 長さ n の係数列、`b`: 長さ m (m <= n) の係数列<br>**戻り値:** std::vector<mint> c[i] = sum_j a[i+j]*b[j] (長さ n - m + 1)<br>**参考:** [https://noshi91.hatenablog.com/entry/2023/12/10/163348](https://noshi91.hatenablog.com/entry/2023/12/10/163348) | $n=\|a\|$ として $O(n\log n)$ |
| `std::vector<std::int64_t> convolution_ll(const std::vector<std::int64_t> &a, const std::vector<std::int64_t> &b)` | 任意係数の畳み込み (3 つの NTT + Garner 法)<br>3 つの NTT-friendly 素数で畳み込み、Garner 法で復元することで オーバーフローしない範囲の int64_t 畳み込みを求める。<br>**引数:** `a`: 入力多項式の係数列、`b`: 入力多項式の係数列<br>**戻り値:** std::vector<std::int64_t> a と b の畳み込み (長さ a.size() + b.size() - 1)<br>**備考:** 畳み込み後の長さは 2^24 (約 1.6e7) 以下でなければならない。 | 出力長を $N$ として $O(N\log N)$ |
| `std::vector<std::int64_t> convolution_ll2(const std::vector<std::int64_t> &a, const std::vector<std::int64_t> &b)` | 係数積が小さいときの畳み込み (2 つの NTT + CRT)<br>MOD1 (= 754974721) と MOD3 (= 469762049) の 2 素数だけで畳み込み、 CRT で復元する。NTT が 1 回少ない分 convolution_ll より速い。<br>**引数:** `a`: 入力多項式の係数列、`b`: 入力多項式の係数列<br>**戻り値:** std::vector<std::int64_t> a と b の畳み込み (長さ a.size() + b.size() - 1)<br>**注意:** 真値が MOD1 * MOD3 (約 3.5e17) 未満であること。畳み込み長 L について 各係数は高々 (max\|a_i\|)*(max\|b_j\|)*L になるので、これがこの上限を超えない 範囲でのみ使う (例: 各係数が 10^5 未満なら長さ 2^24 まで安全)。 係数は非負であること (CRT 復元は [0, MOD1*MOD3) を返す)。<br>**備考:** 畳み込み後の長さは 2^24 (約 1.6e7) 以下でなければならない。 | 出力長を $N$ として $O(N\log N)$ |
| `template <unsigned int mod = 998244353, std::integral T> std::vector<T> convolution_mod(const std::vector<T> &a, const std::vector<T> &b)` | 任意 mod 畳み込み (3 つの NTT + Garner 法)<br>3 つの NTT-friendly 素数で畳み込み、Garner 法で復元した値を mod で取る。 mod は NTT-friendly でなくてもよい。<br>**テンプレート引数:** `mod`: 出力を取る法 (既定: 998244353)、`T`: 整数型 (std::integral)<br>**引数:** `a`: 入力多項式の係数列、`b`: 入力多項式の係数列<br>**戻り値:** std::vector<T> a と b の畳み込みを mod で取った値 (長さ a.size() + b.size() - 1)<br>**注意:** 各係数は [0, mod) の非負整数であること。Garner 復元値を mod で割った 剰余を返すため、負値や mod 以上の値を渡すと正しい結果にならない (真値を mod 還元したい場合は convolution_ll を使うこと)。<br>**備考:** 畳み込み後の長さは 2^24 (約 1.6e7) 以下でなければならない。<br>**参考:** [https://math314.hateblo.jp/entry/2015/05/07/014908](https://math314.hateblo.jp/entry/2015/05/07/014908)、[https://asako.growi.cloud/compro/NTT](https://asako.growi.cloud/compro/NTT) | 出力長を $N$ として $O(N\log N)$ |

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
