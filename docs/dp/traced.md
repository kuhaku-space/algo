---
title: 経路つきDP値 (Traced)
documentation_of: //lib/dp/traced.hpp
compile_example: true
---

DPの値に、そこへ至る経路を相乗りさせる値型。比較は `cost` のみで行い、経路は push が
$O(1)$ の永続スタックで保持する。経路を持ち回っても比較コストは増えないので、DPの
時間計算量は変わらない。

遷移のたびに `then(w, label)` でラベルを積み、最後に `to_vector()` で始点から終点の順に
取り出す。遷移元を記録する配列と、そこを逆向きに辿る復元ループの両方が不要になるので、
「DP本体は書けたが復元でバグる」「DPと復元で遷移の場合分けが食い違う」を避けたいときに使う。

## 使い方

```cpp
#include <vector>
#include "dp/traced.hpp"

// 段 i から i+1 へ a[i]、i+2 へ b[i] のコストで進むときの最小コストと経路
std::vector<long long> a = {2, 5, 1, 3};
std::vector<long long> b = {8, 4, 6};
int n = 5;
constexpr long long inf = 1'000'000'000'000'000'000;

std::vector<Traced<long long>> dp(n, Traced<long long>(inf));
dp[0] = Traced<long long>(0);
for (int i = 0; i < n; ++i) {
    if (dp[i].cost == inf) continue;
    if (i + 1 < n) {
        if (auto cand = dp[i].then(a[i], i + 1); cand < dp[i + 1]) dp[i + 1] = cand;
    }
    if (i + 2 < n) {
        if (auto cand = dp[i].then(b[i], i + 2); cand < dp[i + 2]) dp[i + 2] = cand;
    }
}

long long cost = dp[n - 1].cost;                // 最小コスト
std::vector<int> path = dp[n - 1].to_vector();  // 通った段（始点 0 は含まない）
```

## API

| API | 内容 | 計算量 |
| --- | --- | --- |
| `using value_type = T;` | コストの型 | 型エイリアスで実行時計算量はない |
| `using label_type = Label;` | ラベルの型 | 型エイリアスで実行時計算量はない |
| `using path_type = persistent_stack<Label>;` | 経路を保持する永続スタックの型 | 型エイリアスで実行時計算量はない |
| `T cost;` | 比較に使うコスト | $O(1)$ で参照可能 |
| `path_type path;` | 積んだラベルの列（先頭が最後に積んだラベル） | $O(1)$ で参照可能 |
| `constexpr Traced()` | コストを `T()`、経路を空にして構築する | $O(1)$ |
| `constexpr explicit Traced(T _cost)` | コストを指定し、経路を空にして構築する<br>**備考:** 経路の情報を落とさないよう暗黙変換にはしていない。 | $O(1)$ |
| `constexpr Traced(T _cost, path_type _path)` | コストと経路を直接指定して構築する<br>`then` では表せない結合（`max(cost, w)` を使うボトルネック最短路など）は `Traced(std::max(dp[i].cost, w), dp[i].path.push(label))` のように直接組む。 | $O(1)$ |
| `constexpr auto operator<=>(const Traced &rhs) const`<br>`constexpr bool operator==(const Traced &rhs) const` | `cost` のみで比較する | $O(1)$ |
| `Traced then(const T &w, const Label &label) const` | コストに w を足し、経路に label を積んだ値を返す | $O(1)$ |
| `constexpr int size() const` | 積んだラベルの個数を返す | $O(1)$ |
| `std::vector<Label> to_vector() const` | 積んだラベルを積んだ順（始点から終点）に返す | 経路長を $L$ として $O(L)$ |

## 補足

- `T` には `operator<=>` と `operator+` を要求する。`Label` に要求するのはコピー構築のみ。
- 始点の `Traced` は経路が空なので、`to_vector()` に始点のラベルは含まれない。始点を含めたい
  ときは呼び出し側で先頭に足す。
- 空間計算量は `then` の結果を採用した回数 $U$ について $O(U)$。永続スタックのノードは
  解放しないので、状態数が非常に多いDPでは遷移元を記録する方式のほうがメモリで有利になる。
  最短路のように「1 頂点あたりの緩和回数が辺数で抑えられる」場合は $O(E)$ で収まる。
- 単一の値への `explicit` コンストラクタしか持たないため、`dp[i] = 0` のような代入は
  コンパイルエラーになる。経路を落とす代入を事故で書けないようにするための制約。
- `then` は `cost + w` でコストを合成する。ボトルネック最短路のように別の合成が必要なときは
  `Traced(std::max(dp[i].cost, w), dp[i].path.push(label))` のようにメンバから直接組む。
- 最大化するDPでは比較を反転させるだけでよい（`dp[j] < cand` で更新する）。`cost` に負号を
  付けて最小化に直す必要はない。

## 検証

- [Library Checker Shortest Path](https://judge.yosupo.jp/problem/shortest_path) — ダイクストラ法の
  DP値を `Traced` にして経路を出力し、距離が `graph/shortest_path.hpp` と一致すること、
  出力した経路が実際に辺で繋がっていて重みの和が `cost` と一致することを確認している。
