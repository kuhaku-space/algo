#include "_base.hpp"

// O(|S|)
// R[i] := S[i-(R[i]-1):i] == S[i:i+(R[i]-1)]
template <typename Type>
struct Manacher {
    Type S;
    vector<int64_t> R;

    Manacher(Type S) : S(S) {
        R.resize(S.size());
        int64_t i = 0, j = 0;
        while (i < S.size()) {
            while (i - j >= 0 && i + j < S.size() && S[i - j] == S[i + j]) ++j;
            R[i] = j;
            int64_t k = 1;
            while (i - k >= 0 && i + k < S.size() && k + R[i - k] < j)
                R[i + k] = R[i - k], ++k;
            i += k, j -= k;
        }
    }
};
