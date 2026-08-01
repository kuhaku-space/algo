#include <cstdint>
#include <unordered_map>
#include <utility>

/// @brief 64bit整数キーを必要時に追加する動的Union-Find
/// @complexity `root`・`same`・`unite`・`size` はハッシュ表の期待計算量で
/// 償却 $O(\alpha(n))$、`clear` は $O(n)$
struct dynamic_union_find {
    /// @brief 空の Union-Find を作る
    /// @complexity $O(1)$
    dynamic_union_find() : data() {}

    /// @brief キー `x` を追加し、その集合の代表を返す
    /// @complexity 期待償却 $O(\alpha(n))$
    std::int64_t root(std::int64_t x) {
        if (!data.count(x)) data[x] = -1;
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    /// @brief `root(x)` の別名
    /// @complexity 期待償却 $O(\alpha(n))$
    std::int64_t get_root(std::int64_t x) { return root(x); }

    /// @brief 追加済みのキー `x` が集合の代表なら true を返す
    /// @complexity 期待 $O(1)$
    bool is_root(std::int64_t x) { return data.count(x) && data[x] < 0; }

    /// @brief `x`, `y` が同じ集合なら true を返す
    /// @complexity 期待償却 $O(\alpha(n))$
    bool same(std::int64_t x, std::int64_t y) { return root(x) == root(y); }
    /// @brief `same(x, y)` の別名
    /// @complexity 期待償却 $O(\alpha(n))$
    bool is_same(std::int64_t x, std::int64_t y) { return same(x, y); }

    /// @brief `x` が属する集合の要素数を返す
    /// @complexity 期待償却 $O(\alpha(n))$
    int size(std::int64_t x) { return -data[root(x)]; }
    /// @brief `size(x)` の別名
    /// @complexity 期待償却 $O(\alpha(n))$
    int get_size(std::int64_t x) { return size(x); }

    /// @brief 全てのキーと併合情報を削除する
    /// @complexity $O(n)$
    void clear() { data.clear(); }

    /// @brief `x`, `y` の集合を併合し、新たに併合したかを返す
    /// @complexity 期待償却 $O(\alpha(n))$
    bool unite(std::int64_t x, std::int64_t y) {
        x = root(x), y = root(y);
        if (x == y) return false;
        if (data[x] > data[y]) std::swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    /// @brief `x`, `y` を併合した後、代表 `x`, `y` を `f(x, y)` に渡す
    /// @details 既に同じ集合なら同じ代表を 2 引数へ渡す。
    /// @return 新たに併合したなら true
    /// @complexity 期待償却 $O(\alpha(n))$（`f` の実行時間を除く）
    template <class F>
    bool unite(std::int64_t x, std::int64_t y, F f) {
        x = root(x), y = root(y);
        if (x != y) {
            if (data[x] > data[y]) std::swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        f(x, y);
        return x != y;
    }

  private:
    std::unordered_map<std::int64_t, std::int64_t> data;
};
