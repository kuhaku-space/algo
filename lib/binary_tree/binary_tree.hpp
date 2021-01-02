#include "_base.hpp"

template <class T>
struct binary_tree {
    struct node {
        T key;
        int64_t left, right;

        node() : key(numeric_limits<T>::max()) {}

        node(T _key, int64_t _left, int64_t _right) : key(_key), left(_left), right(_right) {}
    };

    int64_t sz;
    vector<node> nodes;

    binary_tree() {
        sz = 1;
        nodes.resize(sz, node());
    }

    bool operator<(const binary_tree &rhs) const {
        return dfs() < rhs.dfs();
    }

    int64_t find(T key) {
        int64_t it = 0;
        while (nodes[it].key != numeric_limits<T>::max() && nodes[it].key != key) {
            if (key < nodes[it].key) it = nodes[it].left;
            else it = nodes[it].right;
        }
        return it;
    }

    bool exist(T key) {
        return nodes[find(key)].key == key;
    }

    void insert(T key) {
        int64_t it = find(key);
        if (nodes[it].key == key) return;
        nodes.resize(sz + 2, node());
        nodes[it] = node(key, sz, sz + 1);
        sz += 2;
    }

    vector<int64_t> dfs() const {
        vector<int64_t> res;
        stack<int64_t> st;
        st.push(0);
        while (!st.empty()) {
            int64_t t = st.top();
            st.pop();
            if (nodes[t].key == numeric_limits<T>::max()) continue;
            res.push_back(nodes[t].key);
            st.push(nodes[t].right);
            st.push(nodes[t].left);
        }
        return res;
    }
};
