#include "template/template.hpp"
#include "algorithm/xorshift.hpp"

template <class T, int B = 20>
struct skip_list {
    struct Node {
        T val;
        Node* itr[B];

        Node(T _val = T()) : val(_val) {
            for (int i = 0; i < B; ++i) itr[i] = nullptr;
        }
    };

    Node* head;
    Xorshift xor128;

    skip_list() : xor128() { head = new Node(); }

    void insert(T val) {
        int height = 0;
        for (int i = 0; i < B - 1; ++i) {
            if (xor128() & 1) break;
            ++height;
        }

        Node* new_node = new Node(val);
        Node* node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];

            if (i <= height) {
                new_node->itr[i] = node->itr[i];
                node->itr[i] = new_node;
            }
        }
    }

    void erase(T val) {
        Node* node = head;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
        }
        Node* delete_node = node->itr[0]->val == val ? node->itr[0] : nullptr;
        if (!delete_node) return;
        for (int i = B - 1; i >= 0; --i) {
            while (node->itr[i] && node->itr[i]->val < val) node = node->itr[i];
            if (node->itr[i] == delete_node) node->itr[i] = node->itr[i]->itr[i];
        }
    }

    int count(T val) {
        Node* node = head;
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
};
