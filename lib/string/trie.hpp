#include "template/template.hpp"

/**
 * @brief Trie
 *
 * @tparam char_size 文字種
 * @tparam base
 *
 * @see https://algo-logic.info/trie-tree/
 * @see https://atcoder.jp/contests/tenka1-2016-final-open/tasks/tenka1_2016_final_c
 *
 * Usage:
 * Trie<26, 'a'> trie;
 * Trie<96, ' '> trie;
 */
template <int char_size, int base>
struct Trie {
  private:
    struct _node {
        std::vector<int> next_node;
        _node() : next_node(char_size, -1) {}
    };

  public:
    using node_type = _node;

    Trie() : root(0), nodes() { this->nodes.emplace_back(); }

    int size() const noexcept { return this->nodes.size(); }

    std::vector<int> insert(const string &word) {
        std::vector<int> res;
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int c = word[i] - base;
            int &next_id = this->nodes[node_id].next_node[c];
            if (next_id == -1) {
                next_id = this->nodes.size();
                this->nodes.emplace_back();
            }
            node_id = next_id;
            res.emplace_back(node_id);
        }
        return res;
    }

    int search_id(const string &word) {
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int c = word[i] - base;
            int &next_id = this->nodes[node_id].next_node[c];
            if (next_id == -1) return -1;
            node_id = next_id;
        }
        return node_id;
    }

    node_type get_node(int node_id) const {
        assert(0 <= node_id && node_id < (int)this->nodes.size());
        return this->nodes[node_id];
    }

  private:
    int root;
    std::vector<node_type> nodes;
};
