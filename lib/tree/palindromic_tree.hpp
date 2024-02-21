#include <map>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief 回文木
 * @see https://math314.hateblo.jp/entry/2016/12/19/005919
 */
struct palindromic_tree {
  private:
    struct _node {
        using pointer = _node *;

        std::map<char, int> link;
        int suffix_link;
        int len;
        int count;

        _node() : link(), suffix_link(), len(), count() {}
        _node(int _suffix_link, int _len, int _count)
            : link(), suffix_link(_suffix_link), len(_len), count(_count) {}
    };

  public:
    using node_type = _node;
    using node_pointer = typename _node::pointer;

    palindromic_tree() : nodes(), str(), active_idx() {
        create_node(0, -1, 0);
        create_node(0, 0, 0);
    }

    int size() const { return nodes.size(); }

    int get_active_idx() const { return active_idx; }

    node_pointer get_node(int id) { return &nodes[id]; }

    int add(char ch) {
        str.push_back(ch);
        int a = find_prev_palindrome_idx(active_idx);
        auto inserted_result = nodes[a].link.insert(std::make_pair(ch, int(nodes.size())));
        active_idx = inserted_result.first->second;
        if (!inserted_result.second) {
            nodes[active_idx].count++;
            return active_idx;
        }

        node_pointer node = create_node(0, nodes[a].len + 2, 1);
        if (node->len == 1) {
            node->suffix_link = 1;
        } else {
            int b = find_prev_palindrome_idx(nodes[a].suffix_link);
            node->suffix_link = nodes[b].link[ch];
        }
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

    void clear() {
        str.clear();
        active_idx = 0;
    }

  private:
    std::vector<node_type> nodes;
    std::string str;
    int active_idx;

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
