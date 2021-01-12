#include "_base.hpp"

// O(|S|)
// A[i] := S[i:A[i]-1] == S[0:A[i]-1]
template <typename Type>
struct Z_algorithm {
    Type s;
    vector<int64_t> data;

    Z_algorithm(Type _s) : s(_s), data(_s.size()) {
        data[0] = s.size();
        int64_t i = 1, j = 0;
        while (i < s.size()) {
            while (i + j < s.size() && s[j] == s[i + j]) ++j;
            data[i] = j;
            if (!j) {
                ++i;
                continue;
            }
            int64_t k = 1;
            while (i + k < s.size() && k + data[k] < j)
                data[i + k] = data[k], ++k;
            i += k, j -= k;
        }
    }
};
