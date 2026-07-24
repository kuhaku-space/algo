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

### 型

| 型 | 内容 |
| --- | --- |
| `static_modint<m>` | コンパイル時固定の法 `m` |
| `dynamic_modint<id>` | `id` ごとに独立した実行時の法を持つ型 |
| `modint998` | `static_modint<998244353>` |
| `modint107` | `static_modint<1000000007>` |
| `modint` | `dynamic_modint<-1>` |

### 操作

| API | 内容 | 計算量 |
| --- | --- | --- |
| `Mint(value)` | 整数を `[0, mod)` に正規化して構築 | $O(1)$ |
| `val()` | 正規化済みの値を返す | $O(1)$ |
| `mod()` | 現在の法を返す | $O(1)$ |
| `set_mod(m)` | `dynamic_modint` の法を設定 | $O(1)$ |
| `raw(value)` | 正規化を省略して構築 | $O(1)$ |
| `+`, `-`, `*`, `/` と複合代入 | 法上の四則演算 | 除算以外 $O(1)$ |
| `pow(n)` | 非負整数乗 | $O(\log n)$ |
| `inv()` | 乗法逆元 | 素数法で $O(\log m)$ |
| `++`, `--`, `==`, `!=`, `>>`, `<<` | 通常の整数型に対応する操作 | $O(1)$ |

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
