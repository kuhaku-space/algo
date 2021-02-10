#include "_base.hpp"

// verify : https://onlinejudge.u-aizu.ac.jp/problems/2934

// O(|S|)
// R[i] := S[i-(R[i]-1):i] == S[i:i+(R[i]-1)]
template <typename Type>
struct Manacher {
    Type s;
    vector<int64_t> data;

    Manacher(const Type &_s) : s(_s), data(_s.size()) {
        int64_t i = 0, j = 0;
        while (i < s.size()) {
            while (i - j >= 0 && i + j < s.size() && s[i - j] == s[i + j]) ++j;
            data[i] = j;
            int64_t k = 1;
            while (i - k >= 0 && i + k < s.size() && k + data[i - k] < j)
                data[i + k] = data[i - k], ++k;
            i += k, j -= k;
        }
    }

    const int64_t &operator[](int64_t i) const { return data[i]; }
};
