#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"
#include "template/atcoder.hpp"
#include "tree/tree_function.hpp"

int main(void) {
    int n;
    cin >> n;
    Graph<int> g(n);
    g.input_edges(n - 1, 0);
    auto d = tree_dist<int, ll>(g, 0);
    int st = max_element(all(d)) - d.begin();
    d = tree_dist<int, ll>(g, st);
    auto p = tree_parent(g, st);
    int gl = max_element(all(d)) - d.begin();
    vector<int> ans;
    while (gl != -1) {
        ans.emplace_back(gl);
        gl = p[gl];
    }
    co(*max_element(all(d)), ans.size());
    co(ans);

    return 0;
}
