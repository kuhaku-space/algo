#include <algorithm>
#include <vector>

/**
 * @brief KMP法
 *
 * @tparam Container
 *
 * @see https://snuke.hatenablog.com/entry/2014/12/01/235807
 */
template <class Container>
struct knuth_morris_pratt {
    knuth_morris_pratt(const Container &_t) : t(_t), data(_t.size() + 1) {
        data[0] = -1;
        int j = -1;
        for (int i = 0; i < t.size(); ++i) {
            while (j >= 0 && t[i] != t[j]) j = data[j];
            if (t[i + 1] == t[++j]) data[i + 1] = data[j];
            else data[i + 1] = j;
        }
    }

    const int operator[](int i) const { return data[i]; }

    /**
     * @brief 検索
     *
     * @param s 対象列
     * @return std::vector<int>
     */
    std::vector<int> search(const Container &s) {
        int n = s.size(), m = t.size();
        std::vector<int> res(n);
        int i = 0, j = 0;
        while (i + j < n) {
            if (j < m && t[j] == s[i + j]) {
                ++j;
                res[i + j - 1] = j;
                continue;
            }
            i += j - data[j];
            j = std::max(data[j], int(0));
        }
        return res;
    }

  private:
    Container t;
    std::vector<int> data;
};
