#include "segment_tree/segment_tree.hpp"
#include "template/template.hpp"

/**
 * @brief 領域木
 *
 * @tparam M
 * @tparam T
 *
 * @see https://hitonanode.github.io/cplib-cpp/segmenttree/rangetree.hpp.html
 */
template <class M, class T = int>
struct range_tree {
  private:
    using Pt = std::pair<T, T>;
    using value_type = typename M::value_type;

  public:
    range_tree() = default;

    void add(T x, T y) noexcept { _pts.emplace_back(x, y); }

    void build() {
        std::sort(_pts.begin(), _pts.end());
        _pts.erase(std::unique(_pts.begin(), _pts.end()), _pts.end());
        _size = _pts.size();

        _range2yxs.resize(_size * 2);
        for (int i = 0; i < _size; i++) _range2yxs[_size + i] = {{_pts[i].second, _pts[i].first}};
        for (int i = _size - 1; i > 0; i--) {
            auto &lch = _range2yxs[i * 2];
            auto &rch = _range2yxs[i * 2 + 1];
            std::merge(lch.begin(), lch.end(), rch.begin(), rch.end(),
                       std::back_inserter(_range2yxs[i]));
            _range2yxs[i].erase(std::unique(_range2yxs[i].begin(), _range2yxs[i].end()),
                                _range2yxs[i].end());
        }
        for (const auto &v : _range2yxs) segtrees.emplace_back(v.size());
    }

    void set(T x, T y, value_type val) {
        int i = std::distance(_pts.begin(), std::lower_bound(_pts.begin(), _pts.end(), Pt{x, y}));
        assert(i < _size && _pts[i] == std::make_pair(x, y));
        for (i += _size; i; i >>= 1) set(i, {x, y}, val);
    }

    value_type prod(T xl, T yl, T xr, T yr) const {
        auto comp = [](const Pt &l, const Pt &r) {
            return l.first < r.first;
        };
        int l = _size + std::distance(_pts.begin(),
                                      std::lower_bound(_pts.begin(), _pts.end(), Pt{xl, yr}, comp));
        int r = _size + std::distance(_pts.begin(),
                                      std::lower_bound(_pts.begin(), _pts.end(), Pt{xr, yr}, comp));
        value_type res = M::id;
        while (l < r) {
            if (l & 1) res = M::op(res, prod(l++, yl, yr));
            if (r & 1) res = M::op(res, prod(--r, yl, yr));
            l >>= 1, r >>= 1;
        }
        return res;
    }
    value_type get(T x, T y) const { return prod(x, y, x + 1, y + 1); }

  private:
    int _size;
    std::vector<Pt> _pts;
    std::vector<std::vector<Pt>> _range2yxs;
    std::vector<segment_tree<M>> segtrees;

    void set(int v, Pt p, value_type val) {
        auto i = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{p.second, p.first}));
        segtrees[v].set(i, val);
    }

    value_type prod(int v, T yl, T yr) const {
        auto comp = [&](const Pt &l, const Pt &r) {
            return l.first < r.first;
        };
        auto il = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{yl, yl}, comp));
        auto ir = std::distance(
            _range2yxs[v].begin(),
            std::lower_bound(_range2yxs[v].begin(), _range2yxs[v].end(), Pt{yr, yr}, comp));
        return segtrees[v].prod(il, ir);
    }
};
