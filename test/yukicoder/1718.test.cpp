// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1718
#include <algorithm>
#include <iostream>
#include <vector>
#include "graph/graph.hpp"
#include "tree/rerooting.hpp"

// 各始点 X について、全どんぐり頂点を訪れる最小移動数を求める。
// 戻る必要はないので、答 = 2 * |Steiner木(どんぐり ∪ {X}) の辺数| - max(X からどんぐりまでの距離)。
//   - 2 * 辺数 は全辺を往復する分、最後に一番遠いどんぐりへ向かう枝だけ片道で済むので max を引く。

// E(X) = Steiner木(どんぐり ∪ {X}) の辺数。集約型 ESum と確定値型 EKey を分ける 2 型モノイド。
struct ESum {
    bool has;         // この方向（複数方向の集約）にどんぐりがあるか
    long long edges;  // この方向が X の Steiner 木に寄与する辺数
};
struct EKey {
    bool has;     // この部分木にどんぐりがあるか
    long long s;  // この部分木の内部にある Steiner 辺数
};
struct EMonoid {
    using value_type = ESum;
    using key_type = EKey;
    static ESum id() { return {false, 0}; }
    static ESum op(const ESum &a, const ESum &b) { return {a.has || b.has, a.edges + b.edges}; }
    // 辺を渡る: 子部分木にどんぐりがあれば「辺 1 本 + 内部の Steiner 辺」が寄与する。
    template <class W>
    static ESum f(const EKey &k, W) {
        return {k.has, k.has ? k.s + 1 : 0};
    }
    // 頂点で確定: 自身がどんぐりなら has を立てる。内部 Steiner 辺数は子方向の寄与の総和。
    static EKey g(const ESum &s, int is_acorn) { return {is_acorn != 0 || s.has, s.edges}; }
};

// maxdist(X) = X から最も遠いどんぐりまでの距離（辺数）。max モノイド。
struct DMonoid {
    using value_type = long long;
    static constexpr long long NEG = -(1LL << 60);  // どんぐり無しの番兵
    static long long id() { return NEG; }
    static long long op(long long a, long long b) { return std::max(a, b); }
    template <class W>
    static long long f(long long v, W) {
        return v + 1;
    }
    static long long g(long long v, int is_acorn) { return std::max(v, is_acorn != 0 ? 0LL : NEG); }
};

int main() {
    int n, k;
    std::cin >> n >> k;
    csr_graph<void> g(n);
    g.input_edges(n - 1);  // 1-indexed・重みなし無向辺
    std::vector<int> acorn(n, 0);
    for (int i = 0; i < k; ++i) {
        int d;
        std::cin >> d;
        acorn[d - 1] = 1;
    }

    ReRooting<EMonoid, csr_graph<void>, int> rr_e(g, acorn);
    ReRooting<DMonoid, csr_graph<void>, int> rr_d(g, acorn);
    for (int x = 0; x < n; ++x) std::cout << 2 * rr_e[x].s - rr_d[x] << '\n';

    return 0;
}
