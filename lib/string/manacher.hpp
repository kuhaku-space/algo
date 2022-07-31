#include "template/template.hpp"

/**
 * @brief Manacher
 * @details R[i] := S[i-R[i]:i] == S[i:i+R[i]]
 *
 * @tparam Container
 */
template <typename Container>
struct Manacher {
    Manacher(const Container &_s) : _size(_s.size()), s(_s), r(_s.size()) {
        int i = 0, j = 0;
        while (i < this->_size) {
            while (i - j >= 0 && i + j < this->_size && this->s[i - j] == this->s[i + j]) ++j;
            this->r[i] = j;
            int k = 1;
            while (i - k >= 0 && i + k < this->_size && k + this->r[i - k] < j)
                this->r[i + k] = this->r[i - k], ++k;
            i += k, j -= k;
        }
    }

    const auto &operator[](int i) const { return this->r[i]; }
    auto &operator[](int i) { return this->r[i]; }
    const auto begin() const { return this->r.begin(); }
    auto begin() { return this->r.begin(); }
    const auto end() const { return this->r.end(); }
    auto end() { return this->r.end(); }

    const std::vector<int> &get() { return this->r; }

  private:
    int _size;
    const Container &s;
    std::vector<int> r;
};
