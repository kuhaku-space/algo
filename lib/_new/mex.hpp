#include "_base.hpp"

struct MEX {
    int n;
    int sz;
    vector<bool> is_exist;
    vector<int> v;

    MEX() : n(), sz(), is_exist(64) {}

    int operator()() const { return n; }

    void add(int x) {
        ++sz;
        if (sz == is_exist.size()) {
            is_exist.resize(sz << 1);
            int cnt = 0;
            for (int i = 0; i < v.size(); ++i) {
                if (v[i] < is_exist.size()) {
                    if (is_exist[v[i]])
                        --sz;
                    else
                        is_exist[v[i]] = true;
                } else {
                    v[cnt++] = v[i];
                }
            }
            v.erase(v.begin() + cnt, v.end());
        }
        if (x < is_exist.size()) {
            if (is_exist[x])
                --sz;
            else
                is_exist[x] = true;
        } else {
            v.emplace_back(x);
        }
        while (is_exist[n]) ++n;
    }

    int get() const { return n; }
};
