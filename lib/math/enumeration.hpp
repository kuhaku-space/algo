#include "math/combination.hpp"
#include "math/modint.hpp"
#include "template/template.hpp"

template <int mod>
struct Enumeration {
    using mint = ModInt<mod>;

    Enumeration() : combi(), data() {}

    mint stirling(int n, int k) {
        mint res = 0;
        for (int i = 0; i < k; ++i) {
            if (i & 1)
                res -= this->combi(k, k - i) * mint(k - i).pow(n);
            else
                res += this->combi(k, k - i) * mint(k - i).pow(n);
        }
        res *= this->combi.finv(k);
        return res;
    }

    mint bell(int n, int k) {
        this->_init(k);
        mint res = 0;
        for (int i = 0; i <= k; ++i) {
            res += mint(i).pow(n) * this->combi.finv(i) * this->data[k - i];
        }
        return res;
    }

  private:
    Combination<mod> combi;
    vector<mint> data;

    void _init(int n) {
        if (this->data.size() > n) return;
        int m = this->data.size();
        this->data.resize(n + 1);
        for (int i = m; i <= n; ++i) {
            if (i == 0)
                this->data[i] = 1;
            else if (i & 1)
                this->data[i] = this->data[i - 1] - this->combi.finv(i);
            else
                this->data[i] = this->data[i - 1] + this->combi.finv(i);
        }
    }
};
