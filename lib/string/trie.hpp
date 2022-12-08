#include "template/template.hpp"

/**
 * @brief Trie
 * @see https://algo-logic.info/trie-tree/
 *
 * Usage:
 * Trie<26, 'a'> trie;
 * Trie<96, ' '> trie;
 *
 * @tparam char_size
 * @tparam base
 */
template <int char_size, int base>
struct Trie {
    struct Node {
        vector<int> next_node, accept;
        int c, common;
        Node(int _c) : c(_c), common(0), next_node(char_size, -1) {}
    };
    vector<Node> nodes;
    int root;
    Trie() : root(0) { nodes.emplace_back(Node(root)); }

    void insert(const string &word) { insert(word, nodes[0].common); }
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (int i = 0; i < word.size(); ++i) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) {
                next_id = nodes.size();
                nodes.emplace_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].accept.emplace_back(word_id);
    }

    bool search(const string &word, bool prefix = false) {
        int node_id = 0;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) return false;
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }

    int search_id(const string &word) {
        int node_id = 0;
        for (int i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) return -1;
            node_id = next_id;
        }
        return node_id;
    }
};
