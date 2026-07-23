#pragma once
#include <algorithm>
#include <cstdint>
#include <map>
#include <numeric>
#include <utility>
#include <vector>

namespace internal_subset_sum {

/// @brief bits |= bits << shift を O(bits.size()) で行う
inline void shift_or(std::vector<std::uint64_t> &bits, long long shift) {
    if (shift <= 0) return;
    long long word_shift = shift / 64;
    int bit_shift = static_cast<int>(shift % 64);
    long long n = static_cast<long long>(bits.size());
    if (bit_shift == 0) {
        for (long long i = n - 1; i >= word_shift; --i) bits[i] |= bits[i - word_shift];
    } else {
        for (long long i = n - 1; i >= word_shift; --i) {
            std::uint64_t v = bits[i - word_shift] << bit_shift;
            if (i - word_shift - 1 >= 0) v |= bits[i - word_shift - 1] >> (64 - bit_shift);
            bits[i] |= v;
        }
    }
}

}  // namespace internal_subset_sum

/// @brief sum(a) を C として、0 から C までの全ての k について部分和が k になる部分集合が存在するか判定する
/// @param a 各要素の重み（非負）
/// @return res[k] == true iff 部分和が k になる部分集合が存在する（0 <= k <= sum(a)）
/// @see https://codeforces.com/blog/entry/98663 (Subset Sum Speedup 1)
/// @complexity O((sum a) sqrt(sum a) / 64)
std::vector<bool> subset_sum_all(const std::vector<int> &a) {
    std::int64_t c = std::accumulate(a.begin(), a.end(), std::int64_t(0));

    // 同じ重みの要素を二分グループ化し、重みの種類数を O(sqrt(C)) 個に落とす。
    // 重み w が occ 個あるとき、1 個 (occ が奇数) または 2 個 (偶数) を w としてそのまま残し、
    // 残りは重み 2w が floor((occ - 1) / 2) または floor((occ - 2) / 2) 個あるとみなして
    // 後段（重みの昇順）にマージする。到達可能な部分和の集合は変化しない。
    std::map<std::int64_t, std::int64_t> cnt;
    for (int x : a) {
        if (x > 0) ++cnt[x];
    }
    std::vector<std::int64_t> weights;
    for (auto it = cnt.begin(); it != cnt.end(); ++it) {
        std::int64_t w = it->first, occ = it->second;
        weights.push_back(w);
        if (occ % 2 == 0) weights.push_back(w);
        std::int64_t rest = (occ - (occ % 2 == 0 ? 2 : 1)) / 2;
        if (rest > 0) cnt[2 * w] += rest;
    }

    std::vector<std::uint64_t> dp(static_cast<std::size_t>(c / 64) + 1, 0);
    dp[0] = 1;
    for (std::int64_t w : weights) internal_subset_sum::shift_or(dp, w);

    std::vector<bool> res(c + 1);
    for (std::int64_t k = 0; k <= c; ++k) res[k] = ((dp[k / 64] >> (k % 64)) & 1) != 0;
    return res;
}

/// @brief 部分和が C になる部分集合が存在するか判定する
/// @param a 各要素の重み（非負）
/// @param C 目標の部分和
/// @see https://codeforces.com/blog/entry/98663 (Subset Sum Speedup 2)
/// @complexity a の最大値を W として O(N * W)
bool subset_sum(const std::vector<int> &a_orig, int C) {
    std::vector<int> a;
    a.reserve(a_orig.size());
    for (int x : a_orig) {
        if (x > 0) a.push_back(x);
    }
    int n = a.size();
    if (n == 0) return C == 0;
    int max_weight = *std::max_element(a.begin(), a.end());
    int r = 0, sum = 0;
    while (r < n && sum + a[r] <= C) sum += a[r++];
    if (r == n && sum != C) return {};
    std::vector<int> dp(max_weight * 2, -1);
    int offset = C - max_weight + 1;
    dp[sum - offset] = r;
    for (int i = r; i < n; i++) {
        std::vector<int> ndp = dp;
        for (int j = max_weight - 1; j >= 0; j--) ndp[j + a[i]] = std::max(ndp[j + a[i]], ndp[j]);
        for (int j = max_weight * 2 - 1; j >= max_weight; j--) {
            for (int k = ndp[j] - 1; k >= std::max(dp[j], 0); k--) ndp[j - a[k]] = std::max(ndp[j - a[k]], k);
        }
        std::swap(dp, ndp);
    }
    return dp[max_weight - 1] != -1;
}
