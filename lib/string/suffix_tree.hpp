#pragma once
#include <map>
#include <string>
#include <vector>

template <class T>
struct suffix_tree {
    struct node {
        int start, end;
        int link;
        std::map<T, int> next;

        node(int start, int end) : start(start), end(end), link(0) {}

        int len() const { return end - start; }
    };

    std::vector<T> s;
    std::vector<node> nodes;
    int root;
    int active_node;
    int active_edge;
    int active_len;
    int remainder;

    suffix_tree(const std::vector<T> &_s)
        : s(_s), root(0), active_node(0), active_edge(0), active_len(0), remainder(0) {
        nodes.emplace_back(-1, -1);
        for (int i = 0; i < (int)s.size(); ++i) {
            extend(i);
        }
    }

    suffix_tree(const std::string &_s) : root(0), active_node(0), active_edge(0), active_len(0), remainder(0) {
        for (auto c : _s) s.emplace_back(c);
        nodes.emplace_back(-1, -1);
        for (int i = 0; i < (int)s.size(); ++i) {
            extend(i);
        }
    }

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
                if (nodes[next].end == -1) len = s.size() - nodes[next].start; // Open edge

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

                if (last_new_node != 0) {
                    nodes[last_new_node].link = split;
                }
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
