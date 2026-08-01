---
title: 部分永続配列 (PartiallyPersistentArray)
documentation_of: //lib/data_structure/partially_persistent_array.hpp
compile_example: true
---

更新は最新時刻に対してのみ行い、参照は任意の過去時刻に対して行える配列。各要素が
`(時刻, 値)` の履歴を昇順に持つ fat node 方式で、更新は履歴末尾への追加、参照は履歴の
二分探索になる。

「時系列順に配列を書き換えながら、途中の任意の時点の値を後から問い合わせる」場面で使う。
版が分岐する（過去の版を基点に更新する）用途には使えず、その場合は完全永続な
`data_structure/persistent_array.hpp` を使う。

## 使い方

```cpp
#include <vector>
#include "data_structure/partially_persistent_array.hpp"

std::vector<int> a = {3, 1, 4};
PartiallyPersistentArray<int> ppa(a);

ppa.set(0, 10);         // 時刻 1: a = {10, 1, 4}
ppa.set(2, 20);         // 時刻 2: a = {10, 1, 20}

int x = ppa.get(0, 0);  // 3   （時刻 0 の値）
int y = ppa.get(2, 1);  // 4   （時刻 1 の値）
int z = ppa[2];         // 20  （現在時刻の値）

// 外部の時刻を割り当てると、同一時刻に複数要素を更新できる
PartiallyPersistentArray<int> events(3, 0);
events.set(0, 5, 100);
events.set(1, 7, 100);       // 同じ時刻 100 での更新
int w = events.get(1, 100);  // 7
```

## API

| API | 内容 | 計算量 |
| --- | --- | --- |
| `PartiallyPersistentArray()` | 空の配列を構築する | $O(1)$ |
| `PartiallyPersistentArray(int n, T val = T())` | n 個の val を時刻 0 の状態として作る | $O(n)$ |
| `template <class U> PartiallyPersistentArray(const std::vector<U> &v)` | 列 v を時刻 0 の状態として作る | $O(n)$ |
| `int size() const` | 要素数を返す | $O(1)$ |
| `int now() const` | 現在時刻を返す | $O(1)$ |
| `T operator[](int k) const` | 現在時刻における k 番目の値を返す | $O(\log q)$ |
| `T at(int k) const` | `operator[](k)` の別名 | $O(\log q)$ |
| `T get(int k) const` | `operator[](k)` の別名 | $O(\log q)$ |
| `T get(int k, int t) const` | 時刻 t における k 番目の値を返す。t が現在時刻を超える場合は最新の値を返す | $O(\log q)$ |
| `T at(int k, int t) const` | `get(k, t)` の別名 | $O(\log q)$ |
| `int set(int k, T val)` | 時刻を 1 進めて k 番目を val に変更する<br>**戻り値:** 更新後の時刻 | 償却 $O(1)$ |
| `void set(int k, T val, int t)` | 現在時刻以上の時刻 t で k 番目を val に変更し、現在時刻を t にする<br>**備考:** 同一時刻に同じ要素を複数回更新した場合は最後の値が採用される | 償却 $O(1)$ |
| `std::vector<T> to_vector() const` | 現在時刻における配列全体を返す | $O(n\log q)$ |
| `std::vector<T> to_vector(int t) const` | 時刻 t における配列全体を返す | $O(n\log q)$ |

## 補足

- 計算量の $n$ は要素数、$q$ は該当する 1 要素の更新回数を表す。
- 初期状態の時刻は 0。`set(k, val)` は時刻を 1 進めるので、$i$ 回目の更新直後の時刻は $i$ になる。
- 時刻の割り当て方は 2 通りあり、混在させてもよい。`set(k, val)` は現在時刻 + 1 を使い、
  `set(k, val, t)` は指定した t を使う。どちらも時刻が非減少であることを `assert` で要求する。
- `get(k, t)` は t が現在時刻を超えていても有効で、最新の値を返す。外部の時刻をそのまま
  問い合わせに使える。負の t は `assert` で弾く。
- 空間計算量は総更新回数を $Q$ として $O(n + Q)$。値を複製するのは更新した要素だけで、
  永続配列のような経路上のノード複製は発生しない。
- `T` に要求するのはコピー構築と代入のみ。順序や演算は不要。
- 同じく過去参照のみを許す設計として `data_structure/partially_persistent_union_find.hpp` がある。
  こちらも `f(x, t)` の形で時刻を最後の引数に取る。

## 検証

- 素直に対応する検証問題がないため competitive-verifier での verify は保留。naive 実装との
  ランダム比較で、自動時刻進行・外部時刻の割り当て・同一時刻の複数更新・現在時刻を超える参照を確認している。
