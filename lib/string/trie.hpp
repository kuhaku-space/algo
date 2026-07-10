#pragma once
#include <cassert>
#include <string>
#include <vector>

/// @brief Trie
/// @see https://algo-logic.info/trie-tree/
/// @see https://atcoder.jp/contests/tenka1-2016-final-open/tasks/tenka1_2016_final_c
template <int char_size = 96, int base = ' '>
struct Trie {
  private:
    struct Node {
        std::vector<int> next_node;
        int count;
        int depth;
        Node() : next_node(char_size, -1), count(0), depth(0) {}
    };

    static int to_index(char ch) {
        int c = ch - base;
        assert(0 <= c && c < char_size);
        return c;
    }

  public:
    using node_type = Node;

    Trie() : nodes() { nodes.emplace_back(); }

    int size() const { return nodes.size(); }

    /// @brief ノード node_id の子 ch をたどる。無ければ新規作成する。
    /// @return 子ノードの id
    /// @note 到達した子ノードの count を1増やす（その接頭辞を持つ文字列の本数になる）。
    ///       新規作成時は depth（根からの接頭辞長）も設定する。
    int add(int node_id, char ch) {
        assert(0 <= node_id && node_id < (int)nodes.size());
        int c = to_index(ch);
        int &next_id = nodes[node_id].next_node[c];
        if (next_id == -1) {
            next_id = nodes.size();
            nodes.emplace_back();
            nodes[next_id].depth = nodes[node_id].depth + 1;
        }
        ++nodes[next_id].count;
        return next_id;
    }

    std::vector<int> insert(const std::string &word) {
        std::vector<int> res;
        res.reserve(word.size());
        int node_id = 0;
        for (char ch : word) {
            node_id = add(node_id, ch);
            res.emplace_back(node_id);
        }
        return res;
    }

    int search_id(const std::string &word) const {
        int node_id = 0;
        for (char ch : word) {
            int c = to_index(ch);
            int next_id = nodes[node_id].next_node[c];
            if (next_id == -1) return -1;
            node_id = next_id;
        }
        return node_id;
    }

    const node_type &get_node(int node_id) const {
        assert(0 <= node_id && node_id < (int)nodes.size());
        return nodes[node_id];
    }

  private:
    std::vector<node_type> nodes;
};
