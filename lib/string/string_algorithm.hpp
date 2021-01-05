#include "_base.hpp"

// O(|S|)
// A[i] := S[0:A[i]-1] == S[i-A[i]:i-1]
template <typename Type>
struct KMP {
    Type S;
    vector<int64_t> A;

    KMP(Type S) : S(S) {
        A.resize(S.size() + 1);
        A[0] = -1;
        int64_t j = -1;
        for (size_t i = 0; i < S.size(); ++i) {
            while (j >= 0 && S[i] != S[j]) j = A[j];
            ++j;
            // if(S[i + 1] == S[j]) A[i + 1] = A[j];
            // else
            A[i + 1] = j;
        }
    }

    ll search(Type T) {
        int64_t i = 0, j = 0;
        while (i < S.size()) {
            if (S[i] == T[j])
                ++i, ++j;
            else if (!j)
                ++i;
            else
                j = A[j];
        }
        if (j == T.size()) return i - j;
        return -1;
    }
};

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
