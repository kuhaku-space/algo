#include "random/xorshift.hpp"
#include "template/template.hpp"

template <class T, int B = 20, class UniformRandomBitGenerator = Xorshift>
struct skip_list {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        pointer itr[B];

        constexpr _node() : val(), itr{} {}
        constexpr _node(const T &_val) : val(_val), itr{} {}
        constexpr _node(T &&_val) : val(std::move(_val)), itr{} {}
        template <typename... Args>
        constexpr _node(Args &&...args) : val(std::forward<Args>(args)...), itr{} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    skip_list() : head(), gen() { head = new _node(); }

    template <typename... Args>
    void emplace(Args &&...args) {
        node_ptr new_node = new _node(std::forward<Args>(args)...);
        insert_node(new_node);
    }
    void insert(const T &val) {
        node_ptr new_node = new _node(val);
        insert_node(new_node);
    }
    void insert(T &&val) {
        node_ptr new_node = new _node(val);
        insert_node(new_node);
    }

    void erase(const T &val) {
        node_ptr node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
        }

        node_ptr delete_node = node->itr[0]->val == val ? node->itr[0] : nullptr;
        if (!delete_node) return;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
            if (node->itr[i] == delete_node) node->itr[i] = node->itr[i]->itr[i];
        }
    }

    bool contains(const T &val) const {
        node_ptr node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
            if (node->itr[i] && node->itr[i]->val == val) return true;
        }
        return false;
    }

    int count(const T &val) const {
        node_ptr node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
        }

        int res = 0;
        while (node->itr[0] && node->itr[0]->val == val) ++res, node = node->itr[0];
        return res;
    }

  private:
    node_ptr head;
    UniformRandomBitGenerator gen;

    int create_height() {
        int height = 0;
        int rand_num = gen();
        for (int i = 0; i < B - 1; ++i) {
            if (rand_num >> i & 1) break;
            ++height;
        }
        return height;
    }

    void insert_node(node_ptr new_node) {
        node_ptr node = head;
        int height = create_height();
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < new_node->val) node = node->itr[i];

            if (i <= height) {
                new_node->itr[i] = node->itr[i];
                node->itr[i] = new_node;
            }
        }
    }
};
