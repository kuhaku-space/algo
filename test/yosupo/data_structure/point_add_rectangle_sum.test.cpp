// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_rectangle_sum
#include <cassert>
#include <cstdint>
#include <iostream>
#include <tuple>
#include <vector>
#include "data_structure/range_tree.hpp"
#include "segtree/segment_tree_2d.hpp"

int main(void) {
    int n, q;
    std::cin >> n >> q;
    range_tree<Add<std::int64_t>> rt;
    segment_tree_2d<Add<std::int64_t>> st(1000000001, 1000000001);

    std::vector<std::tuple<int, int, int>> points(n);
    for (auto &[x, y, z] : points) {
        std::cin >> x >> y >> z;
        rt.add(x, y);
    }
    std::vector<std::tuple<int, int, int, int, int>> queries(q);
    for (auto &[x, y, z, w, v] : queries) {
        std::cin >> x >> y >> z >> w;
        if (x == 0) rt.add(y, z);
        else std::cin >> v;
    }

    rt.build();
    for (auto [x, y, z] : points) {
        rt.set(x, y, rt.get(x, y) + z);
        st.set(x, y, st.get(x, y) + z);
    }
    for (auto [x, y, z, w, v] : queries) {
        if (x == 0) {
            rt.set(y, z, rt.get(y, z) + w);
            st.set(y, z, st.get(y, z) + w);
        } else {
            auto ans_rt = rt.prod(y, z, w, v);
            auto ans_st = st.prod(y, w, z, v);
            assert(ans_rt == ans_st);
            std::cout << ans_rt << '\n';
        }
    }

    return 0;
}
