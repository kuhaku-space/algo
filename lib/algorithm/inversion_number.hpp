#include "algorithm/compress.hpp"
#include "binary_tree/BIT.hpp"
#include "template/template.hpp"

/**
 * @brief 転倒数を求める
 * 
 * @tparam T 配列の方
 * @param v 配列
 * @return int64_t 転倒数
 */
template <class T>
int64_t inversion_number(const vector<T> &v) {
    Compress<T> cps(v);
    BIT<T> bit(cps.size());

    int64_t res = 0;
    for (int i = v.size() - 1; i >= 0; --i) {
        res += bit.sum(cps.get(v[i]));
        bit.add(cps.get(v[i]), 1);
    }
    return res;
}
