#pragma once
#include <array>
#include <cassert>
#include <queue>
#include <string>
#include <vector>

/// @brief Aho Corasick法
/// @see https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick
/// @see https://ei1333.github.io/library/string/aho-corasick.hpp.html
/// @complexity trieのノード数を $S$、最大深さを $D$ として構築 $O(S(char\_size+D))$
template <int char_size, int base>
struct aho_corasick {
  private:
    struct _node {
        std::array<int, char_size> next_node;
        _node() { next_node.fill(-1); }

        int next(int x) const { return next_node[x]; }
    };

  public:
    /// @brief trieノード型
    /// @complexity 型エイリアスで実行時計算量はない
    using node_type = _node;

    /// @brief 根だけを持つ空のautomatonを構築する
    /// @complexity $O(char\_size)$
    aho_corasick() : _nodes(), _failures() { _nodes.emplace_back(); }

    /// @brief ノード数を返す
    /// @complexity $O(1)$
    int size() const { return _nodes.size(); }

    /// @brief ノードkのfailure linkを返す
    /// @complexity $O(1)$
    int failure(int k) const { return _failures[k]; }

    /// @brief failure link配列をコピーして返す
    /// @complexity $O(S)$
    std::vector<int> failures() const { return _failures; }

    /// @brief failure linkを構築しBFS順のノード列を返す
    /// @complexity $O(S(char\_size+D))$
    std::vector<int> build() {
        _failures = std::vector<int>(size(), 0);
        std::vector<int> ord;
        ord.emplace_back(0);
        for (int k = 0; k < size(); ++k) {
            int x = ord[k];
            for (int i = 0; i < char_size; ++i) {
                int next_x = _nodes[x].next(i);
                if (next_x != -1) {
                    ord.emplace_back(next_x);
                    if (k == 0) continue;
                    int y = x;
                    do {
                        y = _failures[y];
                        int next_y = _nodes[y].next(i);
                        if (next_y != -1) {
                            _failures[next_x] = next_y;
                            break;
                        }
                    } while (y != 0);
                }
            }
        }
        return ord;
    }

    /// @brief wordをtrieへ追加し各prefixのノードIDを返す
    /// @complexity word長を $m$ として $O(m\cdot char\_size)$
    std::vector<int> insert(const std::string &word) {
        std::vector<int> res;
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int next_id = _nodes[node_id].next_node[word[i] - base];
            if (next_id == -1) {
                next_id = _nodes.size();
                _nodes.emplace_back();
                _nodes[node_id].next_node[word[i] - base] = next_id;
            }
            node_id = next_id;
            res.emplace_back(node_id);
        }
        return res;
    }

    /// @brief 状態nowから文字cを読んだ遷移先を返す
    /// @complexity 最大深さを $D$ として $O(D)$
    int search(const char c, int now = 0) {
        int next_id = _nodes[now].next(c - base);
        while (next_id == -1 && now != 0) {
            now = _failures[now];
            next_id = _nodes[now].next(c - base);
        }
        return next_id != -1 ? next_id : 0;
    }

    /// @brief 状態nowから文字列strを読んだ各状態を返す
    /// @complexity 文字列長を $n$、最大深さを $D$ として $O(nD)$
    std::vector<int> search(const std::string &str, int now = 0) {
        std::vector<int> res;
        res.emplace_back(now);
        for (auto c : str) {
            now = search(c, now);
            res.emplace_back(now);
        }
        return res;
    }

    /// @brief node_idのノードをコピーして返す
    /// @complexity $O(char\_size)$
    node_type get_node(int node_id) const {
        assert(0 <= node_id && node_id < size());
        return _nodes[node_id];
    }

  private:
    std::vector<node_type> _nodes;
    std::vector<int> _failures;
};
