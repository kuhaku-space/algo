#include "template/template.hpp"

/**
 * @brief ランレングス圧縮
 *
 * @tparam Container
 * @param v 配列
 * @return auto
 */
template <class Container>
auto run_length_encoding(const Container &v) {
    std::vector<std::pair<std::decay_t<decltype(v[0])>, int>> res;
    for (auto &&e : v) {
        if (res.empty() || res.back().first != e) res.emplace_back(e, 1);
        else ++res.back().second;
    }
    return res;
}
