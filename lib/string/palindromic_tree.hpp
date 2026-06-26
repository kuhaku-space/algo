#pragma once
#include <algorithm>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

/// @brief 回文木 (eertree)
/// @see https://math314.hateblo.jp/entry/2016/12/19/005919
/// @see https://arxiv.org/abs/1403.2431 (series link による回文分割 DP)
///
/// ノード 0 が ODD 根 (len = -1)、ノード 1 が EVEN 根 (len = 0)、相異なる非空回文が 2 番以降。
struct PalindromicTree {
  private:
    struct _node {
        using pointer = _node *;

        std::map<char, int> link;  // 両端に 1 文字加えた回文への辺
        int suffix_link;           // 最長真回文接尾辞
        int len;
        int count;        // 「最長回文接尾辞」としてこのノードが現れた回数（build_frequency 前）
        int num;          // suffix link 木の深さ = この位置で終わる回文接尾辞の個数
        int diff;         // len - len[suffix_link]
        int series_link;  // 同じ diff の等差数列を飛ばす直列リンク（回文分割 DP 用）
        int parent;       // 両端 1 文字を除いた回文ノード（根は -1）
        int first_end;    // 初出現の末尾位置 (0-indexed)。開始位置は first_end - len + 1

        _node() : link(), suffix_link(), len(), count(), num(), diff(), series_link(), parent(-1), first_end(-1) {}
        _node(int _suffix_link, int _len, int _count)
            : link(), suffix_link(_suffix_link), len(_len), count(_count), num(), diff(), series_link(), parent(-1),
              first_end(-1) {}
    };

  public:
    using node_type = _node;
    using node_pointer = typename _node::pointer;

    PalindromicTree() : nodes(), str(), active_idx(), active_log() {
        create_node(0, -1, 0);
        create_node(0, 0, 0);
    }

    int size() const { return nodes.size(); }

    int get_active_idx() const { return active_idx; }

    node_pointer get_node(int id) { return &nodes[id]; }

    /// 各 add で確定した最長回文接尾辞ノードの列（add で構築した文字列に対応）
    const std::vector<int> &suffix_nodes() const { return active_log; }

    int add(char ch) {
        str.push_back(ch);
        int a = find_prev_palindrome_idx(active_idx);
        auto inserted_result = nodes[a].link.insert(std::make_pair(ch, int(nodes.size())));
        active_idx = inserted_result.first->second;
        if (inserted_result.second) {
            create_node(0, nodes[a].len + 2, 1);
            int sl;
            if (nodes[active_idx].len == 1) {
                sl = 1;
            } else {
                int b = find_prev_palindrome_idx(nodes[a].suffix_link);
                sl = nodes[b].link[ch];
            }
            nodes[active_idx].suffix_link = sl;
            nodes[active_idx].num = nodes[sl].num + 1;
            nodes[active_idx].diff = nodes[active_idx].len - nodes[sl].len;
            nodes[active_idx].series_link = (nodes[active_idx].diff == nodes[sl].diff) ? nodes[sl].series_link : sl;
            nodes[active_idx].parent = a;
            nodes[active_idx].first_end = int(str.size()) - 1;
        } else {
            nodes[active_idx].count++;
        }
        active_log.push_back(active_idx);
        return active_idx;
    }

    int move(char ch) {
        str.push_back(ch);
        while (true) {
            active_idx = find_prev_palindrome_idx(active_idx);
            auto it = nodes[active_idx].link.find(ch);
            if (it != nodes[active_idx].link.end()) {
                active_idx = it->second;
                return active_idx;
            }
            if (active_idx == 0) break;
            active_idx = nodes[active_idx].suffix_link;
        }
        return active_idx;
    }

    std::vector<int> build_frequency() {
        std::vector<int> res(nodes.size());
        for (int i = int(nodes.size()) - 1; i > 0; --i) {
            res[i] += nodes[i].count;
            res[nodes[i].suffix_link] += res[i];
        }
        return res;
    }

    /// add で構築した各 prefix s[0, i) の最小回文分割数（長さ |s|+1、dp[0] = 0）。O(n log n)
    std::vector<int> min_factorization() {
        int n = int(active_log.size());
        const int inf = std::numeric_limits<int>::max() / 2;
        std::vector<int> dp(n + 1, inf), g(nodes.size());
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            for (int v = active_log[i - 1]; nodes[v].len > 0; v = nodes[v].series_link) {
                int sl = nodes[v].series_link;
                g[v] = dp[i - nodes[sl].len - nodes[v].diff];
                if (nodes[v].diff == nodes[nodes[v].suffix_link].diff) g[v] = std::min(g[v], g[nodes[v].suffix_link]);
                dp[i] = std::min(dp[i], g[v] + 1);
            }
        }
        return dp;
    }

    /// add で構築した各 prefix s[0, i) の回文分割の場合の数（長さ |s|+1、dp[0] = 1）。O(n log n)
    /// T は long long や modint 等。
    template <class T>
    std::vector<T> count_factorization() {
        int n = int(active_log.size());
        std::vector<T> dp(n + 1, T(0)), g(nodes.size(), T(0));
        dp[0] = T(1);
        for (int i = 1; i <= n; ++i) {
            for (int v = active_log[i - 1]; nodes[v].len > 0; v = nodes[v].series_link) {
                int sl = nodes[v].series_link;
                g[v] = dp[i - nodes[sl].len - nodes[v].diff];
                if (nodes[v].diff == nodes[nodes[v].suffix_link].diff) g[v] += g[nodes[v].suffix_link];
                dp[i] += g[v];
            }
        }
        return dp;
    }

    void clear() {
        str.clear();
        active_idx = 0;
        active_log.clear();
    }

  private:
    std::vector<node_type> nodes;
    std::string str;
    int active_idx;
    std::vector<int> active_log;

    node_pointer create_node(int suffix_link, int len, int count) {
        nodes.emplace_back(suffix_link, len, count);
        return &nodes.back();
    }

    int find_prev_palindrome_idx(int node_id) {
        int pos = int(str.size()) - 1;
        while (true) {
            int opposite_side_idx = pos - 1 - nodes[node_id].len;
            if (opposite_side_idx >= 0 && str[opposite_side_idx] == str.back()) break;
            node_id = nodes[node_id].suffix_link;
        }
        return node_id;
    }
};
