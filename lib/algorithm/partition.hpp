#pragma once
#include <algorithm>
#include <concepts>
#include <vector>

/// @brief 整数の分割を列挙する
namespace integer_partition {

// 1 つの分割は降順の正整数列で表す（例: 5 = 3 + 1 + 1 → {3, 1, 1}）

// n のすべての分割について f を呼ぶ。分割は降順、列挙順は辞書順降順
// （最初が {n}、最後が {1, 1, ..., 1}）。
// f には現在の分割を表す std::vector<int> の const 参照が渡される。
template <std::invocable<const std::vector<int> &> F>
void enumerate(int n, F f) {
    if (n < 0) return;
    std::vector<int> part;
    if (n == 0) {
        f(part);
        return;
    }
    part.push_back(n);
    while (true) {
        f(part);
        // 末尾を分解して辞書順で次に小さい降順列を作る。
        // 末尾の連続する 1 の個数を rem に集める。
        int rem = 0;
        while (!part.empty() && part.back() == 1) {
            ++rem;
            part.pop_back();
        }
        if (part.empty()) break;
        // 直前の要素を 1 減らし、それを上限として残り rem + 1 を貪欲に詰める。
        --part.back();
        int mx = part.back();
        rem += 1;
        while (rem > mx) {
            part.push_back(mx);
            rem -= mx;
        }
        part.push_back(rem);
    }
}

// n をちょうど k 個の正整数の和に分割するものを列挙する。各分割は降順。
// k < 0 や n < k なら何も呼ばれない（n == 0 かつ k == 0 のみ空列を 1 度）。
template <std::invocable<const std::vector<int> &> F>
void enumerate_k(int n, int k, F f) {
    if (k < 0 || n < 0) return;
    if (k == 0) {
        if (n == 0) {
            std::vector<int> empty;
            f(empty);
        }
        return;
    }
    if (n < k) return;
    std::vector<int> part(k);
    // rec(idx, rem, mx): part[idx..) に合計 rem を mx 以下の降順で配分する
    auto rec = [&](auto &&self, int idx, int rem, int mx) -> void {
        int left = k - idx;  // 残りの個数
        if (left == 1) {
            if (1 <= rem && rem <= mx) {
                part[idx] = rem;
                f(part);
            }
            return;
        }
        // この位置の値 v を大きい順に試す。残り left - 1 個へは各 1 以上 v 以下で配る。
        int hi = std::min(mx, rem - (left - 1));            // 残りを 1 ずつ確保
        int lo = std::max(1, (rem + left - 1) / left);      // 残りが v*(left-1) 以下になる下限
        for (int v = hi; v >= lo; --v) {
            part[idx] = v;
            self(self, idx + 1, rem - v, v);
        }
    };
    rec(rec, 0, n, n);
}

// n のすべての分割を収集して返す（列挙順は enumerate と同じ）。
inline std::vector<std::vector<int>> partitions(int n) {
    std::vector<std::vector<int>> res;
    enumerate(n, [&](const std::vector<int> &p) { res.push_back(p); });
    return res;
}

// n をちょうど k 個に分割するものをすべて収集して返す。
inline std::vector<std::vector<int>> partitions_k(int n, int k) {
    std::vector<std::vector<int>> res;
    enumerate_k(n, k, [&](const std::vector<int> &p) { res.push_back(p); });
    return res;
}

}  // namespace integer_partition
