#pragma once
#include <array>
#include <map>
#include <string>
#include <vector>

template <class T = char>
struct suffix_automaton {
    struct node {
        int len;
        int link;
        std::map<T, int> next;

        node(int _len, int _link) : len(_len), link(_link) {}
    };

    std::vector<node> nodes;
    int last;

    suffix_automaton() {
        nodes.emplace_back(0, -1);
        last = 0;
    }

    template <class Container>
    explicit suffix_automaton(const Container &s) : suffix_automaton() {
        for (auto c : s) extend(c);
    }

    void extend(T c) {
        int cur = nodes.size();
        nodes.emplace_back(nodes[last].len + 1, -1);

        int p = last;
        while (p != -1 && nodes[p].next.find(c) == nodes[p].next.end()) {
            nodes[p].next[c] = cur;
            p = nodes[p].link;
        }

        if (p == -1) {
            nodes[cur].link = 0;
        } else {
            int q = nodes[p].next[c];
            if (nodes[p].len + 1 == nodes[q].len) {
                nodes[cur].link = q;
            } else {
                int clone = nodes.size();
                nodes.emplace_back(nodes[p].len + 1, nodes[q].link);
                nodes[clone].next = nodes[q].next;

                while (p != -1) {
                    auto it = nodes[p].next.find(c);
                    if (it != nodes[p].next.end() && it->second == q) {
                        it->second = clone;
                        p = nodes[p].link;
                    } else {
                        break;
                    }
                }
                nodes[q].link = nodes[cur].link = clone;
            }
        }
        last = cur;
    }

    int size() const { return nodes.size(); }
};

template <int ALPHABET_SIZE = 26, char BASE = 'a'>
struct string_suffix_automaton {
    struct node {
        int len;
        int link;
        std::array<int, ALPHABET_SIZE> next;

        node(int _len, int _link) : len(_len), link(_link) {
            next.fill(-1);
        }
    };

    std::vector<node> nodes;
    int last;

    string_suffix_automaton() {
        nodes.emplace_back(0, -1);
        last = 0;
    }

    template <class Container>
    explicit string_suffix_automaton(const Container &s) : string_suffix_automaton() {
        for (auto c : s) extend(c);
    }

    void extend(char c) {
        int v = c - BASE;
        int cur = nodes.size();
        nodes.emplace_back(nodes[last].len + 1, -1);

        int p = last;
        while (p != -1 && nodes[p].next[v] == -1) {
            nodes[p].next[v] = cur;
            p = nodes[p].link;
        }

        if (p == -1) {
            nodes[cur].link = 0;
        } else {
            int q = nodes[p].next[v];
            if (nodes[p].len + 1 == nodes[q].len) {
                nodes[cur].link = q;
            } else {
                int clone = nodes.size();
                nodes.emplace_back(nodes[p].len + 1, nodes[q].link);
                nodes[clone].next = nodes[q].next;

                while (p != -1 && nodes[p].next[v] == q) {
                    nodes[p].next[v] = clone;
                    p = nodes[p].link;
                }
                nodes[q].link = nodes[cur].link = clone;
            }
        }
        last = cur;
    }

    int size() const { return nodes.size(); }
};
