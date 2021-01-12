#include "_base.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/ALDS1_14_B

// O(|S|)
// A[i] := S[0:A[i]-1] == S[i-A[i]:i-1]
template <class Type>
struct KMP {
    Type s;
    vector<int64_t> data;

    KMP(const Type &_s) : s(_s), data(_s.size() + 1) {
        data[0] = -1;
        int64_t j = -1;
        for (size_t i = 0; i < s.size(); ++i) {
            while (j >= 0 && s[i] != s[j]) j = data[j];
            if (s[i + 1] == s[++j])
                data[i + 1] = data[j];
            else
                data[i + 1] = j;
        }
    }

    vector<int64_t> search(const Type &t) {
        vector<int64_t> res;
        int64_t i = 0, j = 0;
        while (i + j < t.size()) {
            if (s[j] == t[i + j]) {
                if (++j != s.size()) continue;
                res.push_back(i);
            }
            i += j - data[j];
            j = max(data[j], int64_t(0));
        }
        return res;
    }
};
