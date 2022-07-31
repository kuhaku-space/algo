#include "template/template.hpp"

/**
 * @brief Z algorithm
 * @details Z[i] := S[i:Z[i]] == S[0:Z[i]-i]
 *
 * @tparam Container
 */
template <class Container>
struct z_algorithm {
    z_algorithm(const Container &_s) : s(_s), z(_s.size()) {
        this->z[0] = this->s.size();
        int i = 1, j = 0;
        while (i < s.size()) {
            while (i + j < (int)this->s.size() && this->s[j] == this->s[i + j]) ++j;
            this->z[i] = j;
            if (!j) {
                ++i;
                continue;
            }
            int k = 1;
            while (i + k < (int)this->s.size() && k + this->z[k] < j)
                this->z[i + k] = this->z[k], ++k;
            i += k, j -= k;
        }
    }

    const auto &operator[](int i) const { return this->z[i]; }
    auto &operator[](int i) { return this->z[i]; }
    const auto begin() const { return this->z.begin(); }
    auto begin() { return this->z.begin(); }
    const auto end() const { return this->z.end(); }
    auto end() { return this->z.end(); }

    const std::vector<int> &get() { return this->z; }

  private:
    const Container &s;
    std::vector<int> z;
};
