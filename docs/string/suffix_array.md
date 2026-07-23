---
title: Suffix Array / LCP Array
documentation_of: //lib/string/suffix_array.hpp
compile_example: true
---

列の全接尾辞を辞書順に並べた開始位置列 Suffix Array と、隣接する接尾辞間の
最長共通接頭辞 LCP Array を構築する。文字列検索、異なる部分文字列の個数、
最長共通部分文字列などに利用できる。

## 使い方

```cpp
#include "string/suffix_array.hpp"

std::string text = "banana";
std::vector<int> sa = suffix_array(text);      // {5, 3, 1, 0, 4, 2}
std::vector<int> lcp = lcp_array(text, sa);    // {1, 3, 0, 0, 2}
```

`sa[i]` は辞書順で `i` 番目の接尾辞が始まる添字。`lcp[i]` は
`text.substr(sa[i])` と `text.substr(sa[i + 1])` の最長共通接頭辞長。

## API

| API | 内容 | 計算量 |
| --- | --- | --- |
| `suffix_array(string)` | バイト文字列の Suffix Array | $O(n)$ |
| `suffix_array(vector<int>, upper)` | 各値が `[0, upper]` の整数列 | $O(n + upper)$ |
| `suffix_array(vector<T>)` | 比較可能な任意の列。座標圧縮して構築 | $O(n\log n)$ |
| `lcp_array(sequence, sa)` | Kasai 法で LCP Array を構築 | $O(n)$ |

Suffix Array の構築には SA-IS を使用し、小さい入力では愚直法またはダブリング法へ
切り替える。

## 補足

- 長さ `n` の入力に対して Suffix Array の長さは `n`。空接尾辞は含まない。
- LCP Array の長さは `n - 1`。`lcp_array` は空列には使えない。
- `vector<int>, upper` 版では全要素が `0 <= value <= upper` を満たす必要がある。
- `string` 版は各文字を0から255の値として扱う。
- パターン検索では Suffix Array 上で二分探索する。多数のLCPクエリには、LCP Arrayと
  RMQ用データ構造を組み合わせる。

## 検証

- [Suffix Array](https://judge.yosupo.jp/problem/suffixarray)
- [Number of Substrings](https://judge.yosupo.jp/problem/number_of_substrings)
- [Longest Common Substring](https://judge.yosupo.jp/problem/longest_common_substring)
- [AOJ ALDS1_14_D Multiple String Matching](https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_D)
