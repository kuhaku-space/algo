#include "lib/template/template.hpp"

int64_t inv_mod(int64_t a, int64_t mod) {
    int64_t b = mod, u = 1, v = 0, t;
    while (b > 0) {
        t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return u >= 0 ? u % mod : (mod - (-u) % mod) % mod;
}

int64_t garner(vector<int64_t> r, vector<int64_t> m, const int mod) {
    int64_t n = r.size();
    r.emplace_back(0);
    m.emplace_back(mod);

    vector<int64_t> coffs(n + 1, 1);
    vector<int64_t> constants(n + 1, 0);
    for (int64_t i = 0; i < n; ++i) {
        int64_t v = (r[i] - constants[i]) * inv_mod(coffs[i], m[i]) % m[i];
        if (v < 0) v += m[i];

        for (int64_t j = i + 1; j < n + 1; ++j) {
            (constants[j] += coffs[j] * v) %= m[j];
            (coffs[j] *= m[i]) %= m[j];
        }
    }

    return constants[n];
}
