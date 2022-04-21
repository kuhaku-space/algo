#include "template/template.hpp"

template <class T>
struct binary_tree {
    struct node {
        T key;
        int left, right;

        node() : key(numeric_limits<T>::max()), left(), right() {}
        node(T _key, int64_t _left, int64_t _right) : key(_key), left(_left), right(_right) {}
    };

    int size;
    vector<node> nodes;

    binary_tree() : size(1), nodes(1) {}

    bool operator<(const binary_tree &rhs) const { return dfs() < rhs.dfs(); }

    const int find(T key) const {
        int it = 0;
        while (nodes[it].key != numeric_limits<T>::max() && nodes[it].key != key) {
            if (key < nodes[it].key) it = nodes[it].left;
            else it = nodes[it].right;
        }
        return it;
    }

    bool exist(T key) const { return nodes[find(key)].key == key; }

    void insert(T key) {
        auto it = find(key);
        if (nodes[it].key == key) return;
        nodes.resize(size + 2, node());
        nodes[it] = node(key, size, size + 1);
        size += 2;
    }

    vector<int> dfs() const {
        vector<int> res;
        stack<int> st;
        st.push(0);
        while (!st.empty()) {
            int t = st.top();
            st.pop();
            if (nodes[t].key == numeric_limits<T>::max()) continue;
            res.emplace_back(nodes[t].key);
            st.push(nodes[t].right);
            st.push(nodes[t].left);
        }
        return res;
    }
};
