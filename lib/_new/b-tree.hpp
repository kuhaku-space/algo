#include "lib/template/template.hpp"

template <int M>
struct b_tree {
    struct node {
        int sz = 0;
        int data[M + 1];
        node* ptr[M + 1];

        void insert(int x) {
            node* p = ptr[0];
            for (int i = 0; i < M; ++i) {
                if (x < data[i]) break;
                p = ptr[i + 1];
            }

            if (p != NULL) {
                p->insert(x);
            } else {
                data[sz++] = x;
                int idx = sz - 1;
                while (idx > 0) {
                    if (data[idx - 1] < data[idx]) break;
                    swap(data[idx - 1], data[idx]);
                    --idx;
                }
            }
        }
    };
    node* root;

    void insert(int x) { data[] }
};
