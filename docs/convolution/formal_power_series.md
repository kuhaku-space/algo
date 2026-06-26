---
title: 形式的冪級数 (FPS)
documentation_of: //lib/convolution/formal_power_series.hpp
---

modint 係数の形式的冪級数を `std::vector<mint>` (添字 `i` が $x^i$ の係数) で表現し、
四則・逆元・log・exp・冪乗・平方根・合成・合成逆・多項式除算・多点評価・補間・Taylor shift を提供する。
すべての関数は名前空間 `fps` 内にある。

NTT-friendly な `mod < 2^30` かつ実行時に AVX2 対応 CPU では、`inv` / `log` / `exp` を
Montgomery + AVX2 NTT 実装へ自動で振り分ける（条件を満たさなければ通常の NTT 実装へフォールバック）。

## 使い方

```cpp
#include "convolution/formal_power_series.hpp"
#include "math/modint.hpp"

using mint = ModInt<998244353>;

std::vector<mint> f = {1, 2, 3};  // 1 + 2x + 3x^2
auto g = fps::inv(f, 5);          // 1 / f を x^5 まで
auto h = fps::exp(f);             // exp(f) を f.size() 項まで (f[0] == 0 が必要)
```

`deg` を省略した版は項数を入力の `size()` と同じにする。

## API

| 関数 | 内容 | 前提 | 計算量 |
| --- | --- | --- | --- |
| `plus(f, g)` | 加算 $f + g$ | — | $O(n)$ |
| `inv(h, deg)` / `inv(h)` | 逆元 $1/h \bmod x^{deg}$ | `h[0] != 0` | $O(deg \log deg)$ |
| `log(h, deg)` / `log(h)` | 対数 $\log h \bmod x^{deg}$ | `h[0] == 1` | $O(deg \log deg)$ |
| `exp(h, deg)` / `exp(h)` | 指数 $\exp h \bmod x^{deg}$ | `h[0] == 0` | $O(deg \log deg)$ |
| `pow(h, m, deg)` / `pow(h, m)` | 冪乗 $h^m \bmod x^{deg}$ | — (負の `m` は `h[0] != 0`) | $O(deg \log deg)$ |
| `sqrt(h, deg)` / `sqrt(h)` | 平方根 $g^2 \equiv h \bmod x^{deg}$ | — (解なしは空列) | $O(deg \log deg)$ |
| `composition(f, g, deg)` / `composition(f, g)` | 合成 $f(g(x)) \bmod x^{deg}$ | — | $O(\lvert f\rvert \cdot deg \log deg)$ |
| `compositional_inverse(f, deg)` / `compositional_inverse(f)` | 合成逆 ($f(g) = g(f) = x \bmod x^{deg}$) | `f[0] == 0`, `f[1] != 0` | $O(deg^2 \log deg)$ |
| `div_mod(f, g)` | 多項式除算 (商と剰余 $f = qg + r$) | `g != 0` | $O(n \log n)$ |
| `div(f, g)` / `mod(f, g)` | 商のみ / 剰余のみ | `g != 0` | $O(n \log n)$ |
| `multipoint_evaluation(f, x)` | 多点評価 $f(x_i)$ | — | $O(n \log^2 n)$ |
| `polynomial_interpolation(x, y)` | 補間 ($f(x_i) = y_i$) | `x_i` は相異なる | $O(n \log^2 n)$ |
| `taylor_shift(f, c)` | $f(x) \to f(x + c)$ | — | $O(n \log n)$ |

## 補足

- **`pow` の挙動**: 最低次の項 $c x^k$ を括り出し $h^m = \exp(m \log(h / (c x^k))) \cdot c^m \cdot x^{km}$
  で計算する。`m == 0` は定数 1 を返す。`m < 0` は $h^{|m|}$ の逆元を返す。
  最低次 $x^k$ が $m$ 乗で `deg` 以上に押し出される場合や全係数 0 の場合は全 0 を返す。
- **`sqrt` の挙動**: 最低次の項 $c x^k$ を括り出し、$k$ が偶数かつ $c$ が平方剰余のときのみ
  $g = x^{k/2} \sqrt{h / x^k}$ をニュートン法 $g \leftarrow (g + h \cdot \mathrm{inv}(g)) / 2$ で求める。
  $h \equiv 0$ は全 0 を返す。$k$ が奇数、または $c$ が平方非剰余で解が存在しない場合は**空列**を返す。
  定数項の平方根は `number_theory/sqrt.hpp` の `sqrt_mod` を用いる。
- **`composition` の挙動**: Horner 法 $((f_{n-1} g + f_{n-2}) g + \cdots) g + f_0$ で評価し、各段で $g$ を掛ける。
  $g$ の DFT を使い回して 1 段あたり NTT 2 回。$f$ を多項式として扱うため $g[0] \neq 0$ でも正しい。
  時間制限の緩い小さな `deg` (Library Checker は `deg <= 8000`) 向け。
- **`compositional_inverse` の挙動**: Lagrange 反転 $g_n = \frac{1}{n}[x^{n-1}] r^n$ ($r = (f/x)^{-1}$) で
  求める。$r$ のべきを順次更新しながら対角成分を取り出し、$r$ の DFT を使い回して 1 段あたり NTT 2 回に抑える。
  時間制限の緩い小さな `deg` (Library Checker は `deg <= 8000`) 向けで、計算量は $O(deg^2 \log deg)$。
- **`log` / `exp` の定数項**: `log` の結果は定数項 0、`exp` の結果は定数項 1。
- **`div_mod` の正規化**: 入力 `f`, `g` の末尾 0 は内部で除去し、返り値の商・剰余も末尾 0 を含まない。
  剰余の次数は $\deg r < \deg g$。
- **多点評価・補間**: 部分積木 (subproduct tree) を構築し剰余木を下降する。点数が少ない部分木は
  Horner 法に切り替え、NTT の定数倍を避ける。補間は多点評価と部分積木を共有する。

## 検証

- [Inv of Formal Power Series](https://judge.yosupo.jp/problem/inv_of_formal_power_series)
- [Log of Formal Power Series](https://judge.yosupo.jp/problem/log_of_formal_power_series)
- [Exp of Formal Power Series](https://judge.yosupo.jp/problem/exp_of_formal_power_series)
- [Pow of Formal Power Series](https://judge.yosupo.jp/problem/pow_of_formal_power_series)
- [Sqrt of Formal Power Series](https://judge.yosupo.jp/problem/sqrt_of_formal_power_series)
- [Composition of Formal Power Series](https://judge.yosupo.jp/problem/composition_of_formal_power_series)
- [Compositional Inverse of Formal Power Series](https://judge.yosupo.jp/problem/compositional_inverse_of_formal_power_series)
- [Division of Polynomials](https://judge.yosupo.jp/problem/division_of_polynomials)
- [Multipoint Evaluation](https://judge.yosupo.jp/problem/multipoint_evaluation)
- [Polynomial Interpolation](https://judge.yosupo.jp/problem/polynomial_interpolation)
- [Polynomial Taylor Shift](https://judge.yosupo.jp/problem/polynomial_taylor_shift)
