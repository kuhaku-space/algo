#include <vector>

/**
 * @brief Z algorithm
 * @details Z[i] := S[i:Z[i]] == S[0:Z[i]-i]
 * @see https://snuke.hatenablog.com/entry/2014/12/03/214243
 *
 * @tparam Container
 */
template <class Container>
std::vector<int> z_algorithm(const Container &s) {
    int n = s.size();
    std::vector<int> res(n);
    res[0] = n;
    int i = 1, j = 0;
    while (i < n) {
        while (i + j < n && s[j] == s[i + j]) ++j;
        res[i] = j;
        if (!j) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < n && k + res[k] < j) res[i + k] = res[k], ++k;
        i += k, j -= k;
    }
    return res;
}
