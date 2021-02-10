#include "_base.hpp"

template <class T>
struct binary_tree {
    struct node {
        T k;
        int64_t l, r;

        node() : k(numeric_limits<T>::max()) {}

        node(T _k, int64_t _l, int64_t _r) : k(_k), l(_l), r(_r) {}
    };

    int64_t size;
    vector<node> nodes;

    binary_tree() {
        size = 1;
        nodes.resize(size, node());
    }

    bool operator<(const binary_tree &rhs) const { return dfs() < rhs.dfs(); }

    const int64_t find(T key) const {
        int64_t it = 0;
        while (nodes[it].key != numeric_limits<T>::max() &&
               nodes[it].key != key) {
            if (key < nodes[it].key)
                it = nodes[it].left;
            else
                it = nodes[it].right;
        }
        return it;
    }

    bool exist(T key) const { return nodes[find(key)].key == key; }

    void insert(T key) {
        int64_t it = find(key);
        if (nodes[it].key == key) return;
        nodes.resize(size + 2, node());
        nodes[it] = node(key, size, size + 1);
        size += 2;
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
