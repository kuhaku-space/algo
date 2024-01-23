#include <cassert>
#include <string>
#include <vector>

/**
 * @brief Aho Corasick 法
 *
 * @tparam char_size
 * @tparam base
 *
 * @see https://naoya-2.hatenadiary.org/entry/20090405/aho_corasick
 * @see https://ei1333.github.io/library/string/aho-corasick.hpp.html
 */
template <int char_size, int base>
struct aho_corasick {
  private:
    struct _node {
        std::vector<int> next_node;
        _node() : next_node(char_size, -1) {}

        int next(int x) const { return this->next_node[x]; }
    };

  public:
    using node_type = _node;

    aho_corasick() : nodes(), failure() { this->nodes.emplace_back(); }

    int size() const noexcept { return this->nodes.size(); }

    std::vector<int> build() {
        this->failure = std::vector<int>(this->size(), 0);
        std::queue<int> que;
        for (int i = 0; i < char_size; ++i) {
            int next_root = this->nodes[0].next(i);
            if (next_root != -1) { que.emplace(next_root); }
        }

        while (!que.empty()) {
            int x = que.front();
            que.pop();
            for (int i = 0; i < char_size; ++i) {
                int next_x = this->nodes[x].next(i);
                if (next_x != -1) {
                    que.emplace(next_x);
                    int y = x;
                    do {
                        y = this->failure[y];
                        int next_y = this->nodes[y].next(i);
                        if (next_y != -1) {
                            this->failure[next_x] = next_y;
                            break;
                        }
                    } while (y != 0);
                }
            }
        }
        return this->failure;
    }

    std::vector<int> insert(const std::string &word) {
        std::vector<int> res;
        int node_id = 0;
        for (int i = 0; i < (int)word.size(); ++i) {
            int &next_id = this->nodes[node_id].next_node[word[i] - base];
            if (next_id == -1) {
                next_id = this->nodes.size();
                this->nodes.emplace_back();
            }
            node_id = next_id;
            res.emplace_back(node_id);
        }
        return res;
    }

    int search(const char c, int now = 0) {
        int next_id = this->nodes[now].next(c - base);
        while (next_id == -1 && now != 0) {
            now = this->failure[now];
            next_id = this->nodes[now].next(c - base);
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
        assert(0 <= node_id && node_id < (int)this->nodes.size());
        return this->nodes[node_id];
    }

  private:
    std::vector<node_type> nodes;
    std::vector<int> failure;
};
