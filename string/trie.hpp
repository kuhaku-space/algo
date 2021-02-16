#include "_base.hpp"

// https://algo-logic.info/trie-tree/#:~:text=Trie%E6%9C%A8%E3%81%AF%E3%80%81%E5%8A%B9%E7%8E%87%E7%9A%84,%E3%81%95%E3%82%92M%20%E3%81%A8%E3%81%97%E3%81%BE%E3%81%97%E3%81%9F%E3%80%82%EF%BC%89

/*
 * Usage:
 * Trie<26, 'a'> trie;
 * Trie<96, ' '> trie;
 */
template <int char_size, int base>
struct Trie {
    struct Node {
        vector<int> next_node, accept;
        int c, common;
        Node(int _c) : c(_c), common(0) { next_node.assign(char_size, -1); }
    };
    vector<Node> nodes;
    int root;
    Trie() : root(0) { nodes.emplace_back(Node(root)); }

    void insert(const string &word) { insert(word, nodes[0].common); }
    void insert(const string &word, int word_id) {
        int node_id = 0;
        for (size_t i = 0; i < word.size(); ++i) {
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
        for (size_t i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) return false;
            node_id = next_id;
        }
        return (prefix) ? true : nodes[node_id].accept.size() > 0;
    }

    int search_id(const string &word) {
        int node_id = 0;
        for (size_t i = 0; i < word.size(); i++) {
            int c = word[i] - base;
            int &next_id = nodes[node_id].next_node[c];
            if (next_id == -1) return -1;
            node_id = next_id;
        }
        return node_id;
    }
};
