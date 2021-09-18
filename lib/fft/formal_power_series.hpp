#include "lib/template/template.hpp"
#include "algo/modint.hpp"
#include "fft/ntt.hpp"

template <class T>
struct formal_power_series {
    vector<T> data;

    formal_power_series(vector<T> _v) : data(_v) {}

    const Mint& operator[](const int64_t x) const { return data[x]; }
    Mint& operator[](const int64_t x) { return data[x]; }

    inline size_t size() const { return data.size(); }

    void resize(size_t _sz) { data.resize(_sz); }

    void pow(int64_t x) {
        int64_t n = size();
        vector<int64_t> ans(n);
        ans[0] = T(1);
        for (; x > 0; x >>= 1) {
            if (x & 1) {
                ntt.convolution_self(ans, data);
                ans.resize(n);
            }
            ntt.convolution_self(data, data);
            data.resize(n);
        }
        swap(data, ans);
    }

    void conv_naive(const formal_power_series& a) {
        int64_t n = size() + a.size() - 1;
        vector<T> ans(n);
        for (int64_t i = 0; i < a.size(); ++i) {
            if (a[i] == 0) continue;
            for (int64_t j = 0; j < size(); ++j) {
                ans[i + j] += data[j] * a[i];
            }
        }
        swap(data, ans);
    }

    // data * (1 - x^n)
    void mul(int64_t n) {
        for (int64_t i = size() - 1; i >= n; --i) data[i] -= data[i - n];
    }

    // data / (1 - x^n)
    void div(int64_t n) {
        for (int64_t i = n; i < size(); ++i) data[i] += data[i - n];
    }

    void cumsum() {
        for (int64_t i = 1; i < size(); ++i) data[i] += data[i - 1];
    }

    void cumsum_inv() {
        for (int64_t i = size() - 1; i > 0; --i) data[i] -= data[i - 1];
    }
};
