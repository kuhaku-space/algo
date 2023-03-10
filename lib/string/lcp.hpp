#include "template/template.hpp"

template <class T>
int longest_common_prefix(const std::vector<T> &a, const std::vector<T> &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}

int longest_common_prefix(const string &a, const string &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}
