// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/261
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include "number_theory/discrete_log.hpp"

// 置換（合成）モノイドが配置（arrangement）に作用する acted_set。
// 作用素・状態ともに長さ n の置換/配置を vector<int> で表す。
// op(a, b)[i] = a[b[i]]（合成）、f(perm, arr)[i] = arr[perm[i]]（作用）。
struct Permutation {
    using value_type = std::vector<int>;
    static inline int n;
    static value_type id() {
        value_type e(n);
        std::iota(e.begin(), e.end(), 0);
        return e;
    }
    static value_type op(const value_type &a, const value_type &b) {
        value_type c(n);
        for (int i = 0; i < n; ++i) c[i] = a[b[i]];
        return c;
    }
    static value_type f(const value_type &perm, const value_type &arr) {
        value_type res(n);
        for (int i = 0; i < n; ++i) res[i] = arr[perm[i]];
        return res;
    }
};

int main(void) {
    int n, k;
    std::cin >> n >> k;
    Permutation::n = n;

    // あみだくじ 1 回分を「配置のスロット入れ替え」を表す置換 base に畳み込む
    std::vector<int> base(n);
    std::iota(base.begin(), base.end(), 0);
    while (k--) {
        int x, y;
        std::cin >> x >> y;
        std::swap(base[x - 1], base[y - 1]);
    }

    // 状態（配置）を一意な文字列キーへ（値域は 1..n なので衝突しない完全キー）
    auto to_key = [](const std::vector<int> &arr) {
        std::string s(arr.size(), '\0');
        for (std::size_t i = 0; i < arr.size(); ++i) s[i] = static_cast<char>(arr[i]);
        return s;
    };

    std::vector<int> start(n);
    std::iota(start.begin(), start.end(), 1);  // 初期配置 [1, 2, ..., n]

    int q;
    std::cin >> q;
    while (q--) {
        std::vector<int> target(n);
        for (auto &e : target) std::cin >> e;
        // base を start に何回作用させれば target になるか（n >= 1）。g(100) < 2^30 より上界は 2^30 で十分。
        long long ans = discrete_log_acted<Permutation, std::vector<int>>(base, start, target, to_key, 1, 1LL << 30);
        std::cout << ans << '\n';
    }

    return 0;
}
