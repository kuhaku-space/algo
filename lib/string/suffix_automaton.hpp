#pragma once
#include <array>
#include <map>
#include <string>
#include <vector>

/// @brief Suffix Automaton
/// @details 任意の比較可能な要素型に対し、部分文字列を受理する最小DFAをオンライン構築する。
/// 固定英字向けには `string_suffix_automaton` を利用できる。
/// @complexity 長さnの構築は `suffix_automaton<T>` が $O(n\log\sigma)$、
/// `string_suffix_automaton` が $O(n)$。状態数は $O(n)$
template <class T = char>
struct suffix_automaton {
    /// @brief Suffix Automatonの1状態
    /// @complexity 状態の構築は $O(1)$
    struct node {
        /// @brief この状態が表す最長文字列の長さ
        /// @complexity $O(1)$
        int len;

        /// @brief suffix link先の状態ID
        /// @complexity $O(1)$
        int link;

        /// @brief 文字ごとの遷移
        /// @complexity 参照・更新は $O(\log\sigma)$
        std::map<T, int> next;

        /// @brief 長さとsuffix linkから状態を構築する
        /// @complexity $O(1)$
        node(int _len, int _link) : len(_len), link(_link) {}
    };

    /// @brief 全状態
    /// @complexity 参照は $O(1)$
    std::vector<node> nodes;

    /// @brief 文字列全体に対応する末尾状態
    /// @complexity 参照は $O(1)$
    int last;

    /// @brief 初期状態だけを持つautomatonを構築する
    /// @complexity $O(1)$
    suffix_automaton() {
        nodes.emplace_back(0, -1);
        last = 0;
    }

    /// @brief 列sからautomatonを構築する
    /// @complexity $O(n\log\sigma)$
    template <class Container>
    explicit suffix_automaton(const Container &s) : suffix_automaton() {
        for (auto c : s) extend(c);
    }

    /// @brief 末尾に文字cを追加する
    /// @complexity 償却 $O(\log\sigma)$
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
                int q_link = nodes[q].link;
                nodes.emplace_back(nodes[p].len + 1, q_link);
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

    /// @brief 現在の照合状態へ文字cを追加した状態と一致長を返す
    /// @complexity 単発最悪 $O(n\log\sigma)$、文字列を順に処理する場合は償却 $O(\log\sigma)$
    std::pair<int, int> next_state(int state, int len, T c) const {
        while (state != 0 && nodes[state].next.find(c) == nodes[state].next.end()) {
            state = nodes[state].link;
            len = nodes[state].len;
        }
        if (nodes[state].next.find(c) != nodes[state].next.end()) {
            state = nodes[state].next.at(c);
            len++;
        }
        return {state, len};
    }

    /// @brief 状態数を返す
    /// @complexity $O(1)$
    int size() const { return nodes.size(); }
};

/// @brief 固定alphabet向けSuffix Automaton
/// @complexity 長さnの構築は $O(n)$、状態数は $O(n)$
template <int ALPHABET_SIZE = 26, char BASE = 'a'>
struct string_suffix_automaton {
    /// @brief 固定alphabet automatonの1状態
    /// @complexity 構築は $O(ALPHABET_SIZE)$
    struct node {
        /// @brief この状態が表す最長文字列の長さ
        /// @complexity $O(1)$
        int len;

        /// @brief suffix link先の状態ID
        /// @complexity $O(1)$
        int link;

        /// @brief 文字ごとの遷移先
        /// @complexity 参照は $O(1)$
        std::array<int, ALPHABET_SIZE> next;

        /// @brief 長さとsuffix linkから状態を構築する
        /// @complexity $O(ALPHABET_SIZE)$
        node(int _len, int _link) : len(_len), link(_link) { next.fill(-1); }
    };

    /// @brief 全状態
    /// @complexity 参照は $O(1)$
    std::vector<node> nodes;

    /// @brief 文字列全体に対応する末尾状態
    /// @complexity 参照は $O(1)$
    int last;

    /// @brief 初期状態だけを持つautomatonを構築する
    /// @complexity $O(ALPHABET_SIZE)$
    string_suffix_automaton() {
        nodes.emplace_back(0, -1);
        last = 0;
    }

    /// @brief 列sからautomatonを構築する
    /// @complexity $O(n\cdot ALPHABET_SIZE)$
    template <class Container>
    explicit string_suffix_automaton(const Container &s) : string_suffix_automaton() {
        for (auto c : s) extend(c);
    }

    /// @brief 末尾に文字cを追加する
    /// @complexity 償却 $O(ALPHABET_SIZE)$
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
                int q_link = nodes[q].link;
                nodes.emplace_back(nodes[p].len + 1, q_link);
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

    /// @brief 現在の照合状態へ文字cを追加した状態と一致長を返す
    /// @complexity 単発最悪 $O(n)$、文字列を順に処理する場合は償却 $O(1)$
    std::pair<int, int> next_state(int state, int len, char c) const {
        int v = c - BASE;
        while (state != 0 && nodes[state].next[v] == -1) {
            state = nodes[state].link;
            len = nodes[state].len;
        }
        if (nodes[state].next[v] != -1) {
            state = nodes[state].next[v];
            len++;
        }
        return {state, len};
    }

    /// @brief 状態数を返す
    /// @complexity $O(1)$
    int size() const { return nodes.size(); }
};
