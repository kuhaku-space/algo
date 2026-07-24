#pragma once
#include <map>
#include <string>
#include <vector>

/// @brief Ukkonen法によるSuffix Tree
/// @details 文字列または終端記号付きの列から、辺を元列上の半開区間で保持する接尾辞木を構築する。
/// @complexity 長さを $n$、遷移の辞書サイズを $\sigma$ として $O(n\log\sigma)$
template <class T>
struct suffix_tree {
    /// @brief 接尾辞木の1ノード
    /// @complexity 遷移の参照・更新は $O(\log\sigma)$
    struct node {
        /// @brief 親辺が表す元列上の半開区間[start,end)
        /// @complexity $O(1)$
        int start, end;

        /// @brief suffix link先のノードID
        /// @complexity $O(1)$
        int link;

        /// @brief 先頭要素ごとの子遷移
        /// @complexity 参照・更新は $O(\log\sigma)$
        std::map<T, int> next;

        /// @brief 親辺の区間からノードを構築する
        /// @complexity $O(1)$
        node(int start, int end) : start(start), end(end), link(0) {}

        /// @brief 親辺の長さを返す
        /// @complexity $O(1)$
        int len() const { return end - start; }
    };

    /// @brief 構築対象の列
    /// @complexity 参照は $O(1)$
    std::vector<T> s;

    /// @brief 全ノード
    /// @complexity 参照は $O(1)$
    std::vector<node> nodes;

    /// @brief 根ノードID
    /// @complexity 参照は $O(1)$
    int root;

    /// @brief Ukkonen法のactive node
    /// @complexity 参照は $O(1)$
    int active_node;

    /// @brief Ukkonen法のactive edge開始位置
    /// @complexity 参照は $O(1)$
    int active_edge;

    /// @brief Ukkonen法のactive edge内長
    /// @complexity 参照は $O(1)$
    int active_len;

    /// @brief 未処理suffix数
    /// @complexity 参照は $O(1)$
    int remainder;

    /// @brief 列sから接尾辞木を構築する
    /// @complexity $O(n\log\sigma)$
    suffix_tree(const std::vector<T> &_s)
        : s(_s), root(0), active_node(0), active_edge(0), active_len(0), remainder(0) {
        nodes.emplace_back(-1, -1);
        for (int i = 0; i < (int)s.size(); ++i) { extend(i); }
    }

    /// @brief 文字列sから接尾辞木を構築する
    /// @complexity $O(n\log\sigma)$
    suffix_tree(const std::string &_s) : root(0), active_node(0), active_edge(0), active_len(0), remainder(0) {
        for (auto c : _s) s.emplace_back(c);
        nodes.emplace_back(-1, -1);
        for (int i = 0; i < (int)s.size(); ++i) { extend(i); }
    }

    /// @brief 位置posまでを木へ追加する
    /// @complexity 全位置を順に追加したとき償却 $O(\log\sigma)$
    void extend(int pos) {
        ++remainder;
        int last_new_node = 0;

        while (remainder > 0) {
            if (active_len == 0) active_edge = pos;

            if (nodes[active_node].next.find(s[active_edge]) == nodes[active_node].next.end()) {
                int leaf = nodes.size();
                nodes.emplace_back(pos, s.size());
                nodes[active_node].next[s[active_edge]] = leaf;

                if (last_new_node != 0) {
                    nodes[last_new_node].link = active_node;
                    last_new_node = 0;
                }
            } else {
                int next = nodes[active_node].next[s[active_edge]];
                int len = nodes[next].len();
                if (nodes[next].end == -1) len = s.size() - nodes[next].start;  // Open edge

                if (active_len >= len) {
                    active_edge += len;
                    active_len -= len;
                    active_node = next;
                    continue;
                }

                if (s[nodes[next].start + active_len] == s[pos]) {
                    if (last_new_node != 0 && active_node != root) {
                        nodes[last_new_node].link = active_node;
                        last_new_node = 0;
                    }
                    ++active_len;
                    break;
                }

                int split = nodes.size();
                nodes.emplace_back(nodes[next].start, nodes[next].start + active_len);
                nodes[active_node].next[s[active_edge]] = split;

                int leaf = nodes.size();
                nodes.emplace_back(pos, s.size());
                nodes[split].next[s[pos]] = leaf;

                nodes[next].start += active_len;
                nodes[split].next[s[nodes[next].start]] = next;

                if (last_new_node != 0) { nodes[last_new_node].link = split; }
                last_new_node = split;
            }

            --remainder;
            if (active_node == root && active_len > 0) {
                --active_len;
                active_edge = pos - remainder + 1;
            } else if (active_node != root) {
                active_node = nodes[active_node].link;
            }
        }
    }
};
