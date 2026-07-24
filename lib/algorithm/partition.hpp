#pragma once
#include <algorithm>
#include <concepts>
#include <vector>

/// @brief 整数の分割を列挙する
namespace integer_partition {

// 1 つの分割は降順の正整数列で表す（例: 5 = 3 + 1 + 1 → {3, 1, 1}）

/// @brief nの全ての整数分割についてfを呼ぶ
/// @details 分割は降順、列挙順は辞書順降順。
/// @complexity 分割数を $P(n)$ として $O(nP(n))$
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

/// @brief nをちょうどk個の正整数へ分割した全ての列についてfを呼ぶ
/// @details 各分割は降順。
/// @complexity 対象となる分割数を $P_k(n)$ として $O(kP_k(n))$
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
        int hi = std::min(mx, rem - (left - 1));        // 残りを 1 ずつ確保
        int lo = std::max(1, (rem + left - 1) / left);  // 残りが v*(left-1) 以下になる下限
        for (int v = hi; v >= lo; --v) {
            part[idx] = v;
            self(self, idx + 1, rem - v, v);
        }
    };
    rec(rec, 0, n, n);
}

/// @brief nの全ての整数分割を返す
/// @complexity 分割数を $P(n)$ として時間・出力サイズともに $O(nP(n))$
inline std::vector<std::vector<int>> partitions(int n) {
    std::vector<std::vector<int>> res;
    enumerate(n, [&](const std::vector<int> &p) { res.push_back(p); });
    return res;
}

/// @brief nをちょうどk個に分割した全ての列を返す
/// @complexity 対象となる分割数を $P_k(n)$ として時間・出力サイズともに $O(kP_k(n))$
inline std::vector<std::vector<int>> partitions_k(int n, int k) {
    std::vector<std::vector<int>> res;
    enumerate_k(n, k, [&](const std::vector<int> &p) { res.push_back(p); });
    return res;
}

}  // namespace integer_partition
