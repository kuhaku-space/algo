#include "template/template.hpp"

/**
 * @brief 最長共通接頭辞
 *
 * @tparam T 配列の型
 * @param a 配列
 * @param b 配列
 * @return int 最長共通接頭辞の長さ
 */
template <class T>
int longest_common_prefix(const std::vector<T> &a, const std::vector<T> &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}

/**
 * @brief 最長共通接頭辞
 *
 * @param a 文字列
 * @param b 文字列
 * @return int 最長共通接頭辞の長さ
 */
int longest_common_prefix(const std::string &a, const std::string &b) {
    int m = (int)std::min(a.size(), b.size());
    for (int i = 0; i < m; ++i) {
        if (a[i] != b[i]) return i;
    }
    return m;
}
