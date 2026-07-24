---
title: 形式的冪級数 (FPS)
documentation_of: //lib/convolution/formal_power_series.hpp
compile_example: true
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

using mint = modint998;

std::vector<mint> f = {1, 2, 3};  // 1 + 2x + 3x^2
auto g = fps::inv(f, 5);          // 1 / f を x^5 まで
std::vector<mint> e = {0, 2, 3};
auto h = fps::exp(e);             // exp(e) を e.size() 項まで (e[0] == 0 が必要)
```

`deg` を省略した版は項数を入力の `size()` と同じにする。

## API

| API | 内容 | 計算量 |
| --- | --- | --- |
| `template <internal::static_modint_c mint> std::vector<mint> fps::plus(const std::vector<mint> &f, const std::vector<mint> &g)` | 形式的冪級数の加算<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 係数列、`g`: 係数列<br>**戻り値:** std::vector<mint> f + g (長さ max(f.size(), g.size())) | $O(\max(\|f\|,\|g\|))$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::inv(const std::vector<mint> &h, int deg)` | 逆元 1 / h (mod x^deg)<br>ニュートン法で deg 項まで求める。定数項 h[0] は逆元を持つ必要がある。 条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列 (h[0] != 0 が必要)、`deg`: 求める項数<br>**戻り値:** std::vector<mint> h * res ≡ 1 (mod x^deg) を満たす res (長さ deg) | O(deg log deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::inv(const std::vector<mint> &h)` | 逆元 1 / h (deg は h.size())<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列 (h[0] != 0 が必要)<br>**戻り値:** std::vector<mint> 長さ h.size() の逆元 | $n=\|h\|$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::log(const std::vector<mint> &h, int deg)` | 対数 log h (mod x^deg)<br>log h = ∫ h' / h dx で求める。定数項 h[0] == 1 が必要。 条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列 (h[0] == 1 が必要)、`deg`: 求める項数<br>**戻り値:** std::vector<mint> log h (長さ deg, 定数項は 0) | O(deg log deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::log(const std::vector<mint> &h)` | 対数 log h (deg は h.size())<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列 (h[0] == 1 が必要)<br>**戻り値:** std::vector<mint> 長さ h.size() の log h | $n=\|h\|$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::exp(const std::vector<mint> &h, int deg)` | 指数 exp h (mod x^deg)<br>ニュートン法で求める。定数項 h[0] == 0 が必要。 条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列 (h[0] == 0 が必要)、`deg`: 求める項数<br>**戻り値:** std::vector<mint> exp h (長さ deg, 定数項は 1) | O(deg log deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::exp(const std::vector<mint> &h)` | 指数 exp h (deg は h.size())<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列 (h[0] == 0 が必要)<br>**戻り値:** std::vector<mint> 長さ h.size() の exp h | $n=\|h\|$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::pow(const std::vector<mint> &h, std::int64_t m, int deg)` | 冪乗 h^m (mod x^deg)<br>最低次の項 c x^k を括り出し pow = exp(m log(h / (c x^k))) * c^m * x^{k m} で求める。 m が負なら h^{\|m\|} の逆元を返す (h[0] != 0 が必要)。最低次が x^k のとき x^{k m} が deg 以上に押し出される場合や全係数 0 の場合は全 0 を返す。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列、`m`: 指数 (負も可)、`deg`: 求める項数<br>**戻り値:** std::vector<mint> h^m (長さ deg)。m == 0 は定数 1 を返す | O(deg log deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::pow(const std::vector<mint> &h, std::int64_t m)` | 冪乗 h^m (deg は h.size())<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列、`m`: 指数 (負も可)<br>**戻り値:** std::vector<mint> 長さ h.size() の h^m | $n=\|h\|$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::sqrt(const std::vector<mint> &h, int deg)` | 平方根 sqrt h (mod x^deg)<br>g^2 ≡ h (mod x^deg) を満たす g を求める。最低次の項 c x^k を括り出し、 k が偶数かつ c が平方剰余のとき g = x^{k/2} sqrt(h / x^k) をニュートン法で求める。 ニュートン法は g = sqrt と g^{-1} を併走させ各段で DFT を使い回す (full inverse の再計算を避ける)。条件を満たせば Montgomery + AVX2 NTT 実装へ振り分ける。 k が奇数、または c が平方非剰余で解が存在しない場合は空列を返す。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列、`deg`: 求める項数<br>**戻り値:** std::vector<mint> g^2 ≡ h を満たす g (長さ deg)。解なしのときは空列 | O(deg log deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::sqrt(const std::vector<mint> &h)` | 平方根 sqrt h (deg は h.size())<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `h`: 係数列<br>**戻り値:** std::vector<mint> 長さ h.size() の sqrt h。解なしのときは空列 | $n=\|h\|$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::composition(const std::vector<mint> &outer, const std::vector<mint> &inner, int deg)` | 合成 (composition) f(g(x)) (mod x^deg)<br>h(x) = f(g(x)) = Σ f[i] g(x)^i (mod x^deg) を Kinoshita-Suzuki の分割統治で求める。 Nyaan の composition は g(f(x)) を返すため f と g を入れ替えて呼び出す。 f は多項式として扱うため g[0] != 0 でも正しく計算できる。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 外側の係数列、`g`: 内側の係数列、`deg`: 求める項数<br>**戻り値:** std::vector<mint> f(g(x)) (長さ deg)<br>**参考:** [https://nyaannyaan.github.io/library/fps/fps-composition.hpp](https://nyaannyaan.github.io/library/fps/fps-composition.hpp) | O(deg log^2 deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::composition(const std::vector<mint> &f, const std::vector<mint> &g)` | 合成 (composition) f(g(x)) (deg は max(f.size(), g.size()))<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 外側の係数列、`g`: 内側の係数列<br>**戻り値:** std::vector<mint> f(g(x)) | $n=\max(\|f\|,\|g\|)$ として $O(n\log^2 n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::compositional_inverse(const std::vector<mint> &f, int deg)` | 合成逆 (compositional inverse) g (mod x^deg)<br>f(g(x)) = g(f(x)) = x (mod x^deg) を満たす g を求める。f[0] == 0 かつ f[1] != 0 が前提。 Kinoshita-Suzuki の power projection (pow_enumerate) で [x^n] f(x)^k を列挙し、 Lagrange-Bürmann 反転 g = (n^{-1} log(rev(h)/h0))^{-1} の exp で復元する (h_k = n [x^k] (列挙結果) / k)。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 係数列 (f[0] == 0, f[1] != 0 が必要)、`deg`: 求める項数<br>**戻り値:** std::vector<mint> g(x) (長さ deg, g[0] == 0)<br>**参考:** [https://nyaannyaan.github.io/library/fps/compositional-inverse.hpp](https://nyaannyaan.github.io/library/fps/compositional-inverse.hpp) | O(deg log^2 deg) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::compositional_inverse(const std::vector<mint> &f)` | 合成逆 (compositional inverse) g (deg は f.size())<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 係数列 (f[0] == 0, f[1] != 0 が必要)<br>**戻り値:** std::vector<mint> 長さ f.size() の g(x) | $n=\|f\|$ として $O(n\log^2 n)$ |
| `template <internal::static_modint_c mint> std::pair<std::vector<mint>, std::vector<mint>> fps::div_mod(std::vector<mint> f, std::vector<mint> g)` | 多項式の除算 (商と剰余)<br>f = q * g + r を満たす商 q と剰余 r (deg r < deg g) を求める。 反転して逆元を掛ける標準的な手法。f, g の末尾 0 は内部で除去する。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 被除多項式の係数列、`g`: 除多項式の係数列 (0 多項式でないこと)<br>**戻り値:** std::pair<商 q, 剰余 r> (どちらも末尾 0 を含まない) | O(n log n) (n = deg f) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::div(const std::vector<mint> &f, const std::vector<mint> &g)` | 多項式の商 f / g<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 被除多項式の係数列、`g`: 除多項式の係数列 (0 多項式でないこと)<br>**戻り値:** std::vector<mint> 商 q | $n=\max(\|f\|,\|g\|)$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::mod(const std::vector<mint> &f, const std::vector<mint> &g)` | 多項式の剰余 f mod g<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 被除多項式の係数列、`g`: 除多項式の係数列 (0 多項式でないこと)<br>**戻り値:** std::vector<mint> 剰余 r (deg r < deg g) | $n=\max(\|f\|,\|g\|)$ として $O(n\log n)$ |
| `template <internal::static_modint_c mint> std::vector<mint> fps::multipoint_evaluation(const std::vector<mint> &f, const std::vector<mint> &x)` | 多点評価<br>部分積木を構築し剰余木を下降して、f を各点 x_i で同時に評価する。 点数が少ない部分木は Horner 法に切り替えて NTT の定数倍を避ける。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 評価する多項式の係数列、`x`: 評価する点の列<br>**戻り値:** std::vector<mint> f(x_i) の列 (長さ x.size()) | O(n log^2 n) (n = max(deg f, \|x\|)) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::polynomial_interpolation(const std::vector<mint> &x, const std::vector<mint> &y)` | 多項式補間 (ラグランジュ補間)<br>相異なる点 (x_i, y_i) を通る次数 n-1 以下の多項式を求める。部分積木を多点評価と 共有し、葉に y_i / f'(x_i) を置いて上向きに畳み込んで復元する。x_i は相異なること。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `x`: 評価点の列 (相異なる)、`y`: 各点での値の列 (x と同じ長さ)<br>**戻り値:** std::vector<mint> f(x_i) = y_i を満たす係数列 (長さ x.size()) | O(n log^2 n) (n = \|x\|) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::taylor_shift(std::vector<mint> f, mint c)` | Taylor shift (係数の平行移動)<br>f(x) の係数から g(x) = f(x + c) の係数を求める。f[i] に i! を掛けて反転し、 c^j / j! との畳み込みの中央部を取り出す標準的な手法。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 係数列 f(x)、`c`: シフト量<br>**戻り値:** std::vector<mint> f(x + c) の係数列 (f と同じ長さ) | O(n log n) (n = f.size()) |
| `template <internal::static_modint_c mint> std::vector<mint> fps::shift_of_sampling_points(const std::vector<mint> &y, mint c, int m)` | 標本点のシフト (shift of sampling points)<br>次数 < n の多項式 f の標本値 y_i = f(i) (i = 0..n-1) から f(c), f(c+1), ..., f(c+m-1) を求める。 ラグランジュ補間 f(x) = (prod_k (x-k)) * sum_i a_i / (x-i) を、係数 a_i = y_i / prod_{k!=i}(i-k) と 1/(c+t) の畳み込みで一括評価する。 評価点 c+j が標本点 {0..n-1} と一致する (区間積が 0 になる) 場合は y を直接返す。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `y`: 標本値の列 f(0..n-1)、`c`: シフト量、`m`: 求める項数<br>**戻り値:** std::vector<mint> f(c+j) の列 (j = 0..m-1, 長さ m) | O((n + m) log(n + m)) |
| `template <internal::static_modint_c mint> std::optional<std::vector<mint>> fps::inv_of_polynomials(const std::vector<mint> &f, const std::vector<mint> &g)` | 多項式の逆元 (modular inverse of polynomials)<br>f(x) * h(x) ≡ 1 (mod g(x)) かつ deg h < deg g を満たす h を Half-GCD による拡張 Euclid 互除法で求める。 逆元が存在する (gcd(f, g) が定数) ときのみ値を返し、存在しなければ std::nullopt を返す。 返り値は末尾 0 を除いた正規形 (逆元が 0 多項式のときは空列)。<br>**テンプレート引数:** `mint`: static modint<br>**引数:** `f`: 係数列 (最高次係数 != 0)、`g`: 法多項式の係数列 (最高次係数 != 0)<br>**戻り値:** std::optional<std::vector<mint>> 逆元 h (deg h < deg g)。逆元が無ければ std::nullopt | O(n log^2 n) (n = max(deg f, deg g)) |

## 補足

- **`pow` の挙動**: 最低次の項 $c x^k$ を括り出し $h^m = \exp(m \log(h / (c x^k))) \cdot c^m \cdot x^{km}$
  で計算する。`m == 0` は定数 1 を返す。`m < 0` は $h^{|m|}$ の逆元を返す。
  最低次 $x^k$ が $m$ 乗で `deg` 以上に押し出される場合や全係数 0 の場合は全 0 を返す。
- **`sqrt` の挙動**: 最低次の項 $c x^k$ を括り出し、$k$ が偶数かつ $c$ が平方剰余のときのみ
  $g = x^{k/2} \sqrt{h / x^k}$ をニュートン法 $g \leftarrow (g + h \cdot \mathrm{inv}(g)) / 2$ で求める。
  $h \equiv 0$ は全 0 を返す。$k$ が奇数、または $c$ が平方非剰余で解が存在しない場合は**空列**を返す。
  定数項の平方根は `number_theory/sqrt.hpp` の `sqrt_mod` を用いる。
- **`composition` の挙動**: Kinoshita-Suzuki の分割統治で $O(deg \log^2 deg)$。
  $f$ を多項式として扱うため $g[0] \neq 0$ でも正しい。
- **`compositional_inverse` の挙動**: Kinoshita-Suzuki の power projection ($[x^n] f(x)^k$ の列挙) を用いた
  Lagrange-Bürmann 反転で $O(deg \log^2 deg)$。
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
