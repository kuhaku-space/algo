#include "lib/template/template.hpp"

vector<int> make_permutation_one_bit(int n, int a, int b) {
    if (n == 1) {
        return {a, b};
    }
    assert(__builtin_parity(a) != __builtin_parity(b));
    int bit = 1 << (n - 1);
    if ((a ^ b) & bit) {
        auto res = make_permutation_one_bit(n - 1, a, a ^ 1);
        auto v = make_permutation_one_bit(n - 1, (a ^ 1) ^ bit, b);
        res.insert(res.end(), v.begin(), v.end());
        return res;
    } else {
        auto res = make_permutation_one_bit(n - 1, a, b);
        auto v = make_permutation_one_bit(n - 1, a ^ bit, res[1] ^ bit);
        res.insert(res.begin() + 1, v.begin(), v.end());
        return res;
    }
}
