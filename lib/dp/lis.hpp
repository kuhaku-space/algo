#include "template/template.hpp"

template <class T>
int LIS(const vector<T> &v) {
    int n = v.size();
    vector<T> dp;
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(dp.begin(), dp.end(), v[i]);
        if (it == dp.end())
            dp.emplace_back(v[i]);
        else
            *it = v[i];
    }
    return dp.size();
}
