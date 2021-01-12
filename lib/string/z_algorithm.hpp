#include "_base.hpp"

// O(|S|)
// A[i] := S[i:A[i]-1] == S[0:A[i]-1]
template <typename Type>
struct Z_algorithm {
    Type S;
    vector<ll> A;

    Z_algorithm(Type S) : S(S) {
        A.resize(S.size());
        A[0] = S.size();
        int64_t i = 1, j = 0;
        while (i < S.size()) {
            while (i + j < S.size() && S[j] == S[i + j]) ++j;
            A[i] = j;
            if (!j) {
                ++i;
                continue;
            }
            int64_t k = 1;
            while (i + k < S.size() && k + A[k] < j) A[i + k] = A[k], ++k;
            i += k, j -= k;
        }
    }
};
