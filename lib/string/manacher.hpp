#include <vector>

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
        while (i < _size) {
            while (i - j >= 0 && i + j < _size && s[i - j] == s[i + j]) ++j;
            r[i] = j;
            int k = 1;
            while (i - k >= 0 && i + k < _size && k + r[i - k] < j) r[i + k] = r[i - k], ++k;
            i += k, j -= k;
        }
    }

    const auto &operator[](int i) const { return r[i]; }
    auto &operator[](int i) { return r[i]; }
    const auto begin() const { return r.begin(); }
    auto begin() { return r.begin(); }
    const auto end() const { return r.end(); }
    auto end() { return r.end(); }

    const std::vector<int> &get() { return r; }

  private:
    int _size;
    const Container &s;
    std::vector<int> r;
};
