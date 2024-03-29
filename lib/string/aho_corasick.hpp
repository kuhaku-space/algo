#include <cassert>
#include <queue>
#include <string>
#include <vector>

/**
 * @brief Aho Corasick 法
 * @see https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick
 * @see https://ei1333.github.io/library/string/aho-corasick.hpp.html
 *
 * @tparam char_size
 * @tparam base
 */
template <int char_size, int base>
struct aho_corasick {
  private:
    struct _node {
        std::vector<int> next_node;
        _node() : next_node(char_size, -1) {}

        int next(int x) const { return next_node[x]; }
    };

  public:
    using node_type = _node;

    aho_corasick() : nodes(), failure() { nodes.emplace_back(); }

    int size() const noexcept { return nodes.size(); }

    std::vector<int> build() {
        failure = std::vector<int>(size(), 0);
        std::queue<int> que;
        for (int i = 0; i < char_size; ++i) {
            int next_root = nodes[0].next(i);
            if (next_root != -1) { que.emplace(next_root); }
        }

        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i < char_size; ++i) {
                int next_x = nodes[x].next(i);
                if (next_x != -1) {
                    que.emplace(next_x);
                    int y = x;
                    do {
                        y = failure[y];
                        int next_y = nodes[y].next(i);
                        if (next_y != -1) {
                            failure[next_x] = next_y;
                            break;
                        }
                    } while (y != 0);
                }
            }
        }
        return failure;
    }

    std::vector<int> insert(const std::string &word) {
        std::vector<int> res;
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int &next_id = nodes[node_id].next_node[word[i] - base];
            if (next_id == -1) {
                next_id = nodes.size();
                nodes.emplace_back();
            }
            node_id = next_id;
            res.emplace_back(node_id);
        }
        return res;
    }

    int search(const char c, int now = 0) {
        int next_id = nodes[now].next(c - base);
        while (next_id == -1 && now != 0) {
            now = failure[now];
            next_id = nodes[now].next(c - base);
        }
        return next_id != -1 ? next_id : 0;
    }

    std::vector<int> search(const std::string &str, int now = 0) {
        std::vector<int> res;
        res.emplace_back(now);
        for (auto c : str) {
            now = search(c, now);
            res.emplace_back(now);
        }
        return res;
    }

    node_type get_node(int node_id) const {
        assert(0 <= node_id && node_id < (int)nodes.size());
        return nodes[node_id];
    }

  private:
    std::vector<node_type> nodes;
    std::vector<int> failure;
};
