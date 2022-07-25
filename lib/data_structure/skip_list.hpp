#include "random/xorshift.hpp"
#include "template/template.hpp"

template <class T, int B = 20, class UniformRandomBitGenerator = Xorshift>
struct skip_list {
  private:
    struct _node {
        using pointer = _node *;
        T val;
        pointer itr[B];

        _node() : _node(T()) {}
        _node(T _val) : val(_val), itr{} {}
    };

  public:
    using node_ptr = typename _node::pointer;

    skip_list() : head(), gen() { this->head = new _node(); }

    void emplace(T val) { this->insert(val); }
    void insert(T val) {
        int height = 0;
        for (int i = 0; i < B - 1; ++i) {
            if (this->gen() & 1) break;
            ++height;
        }

        node_ptr new_node = new _node(val);
        node_ptr node = this->head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];

            if (i <= height) {
                new_node->itr[i] = node->itr[i];
                node->itr[i] = new_node;
            }
        }
    }

    void erase(T val) {
        node_ptr node = this->head;
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

    bool contains(T val) {
        node_ptr node = this->head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
            if (node->itr[i] && node->itr[i]->val == val) return true;
        }
        return false;
    }

    int count(T val) {
        node_ptr node = this->head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
        }

        int res = 0;
        while (node->itr[0] && node->itr[0]->val == val) {
            ++res;
            node = node->itr[0];
        }
        return res;
    }

  private:
    node_ptr head;
    UniformRandomBitGenerator gen;
};
