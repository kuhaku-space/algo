#pragma once
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

/// @brief 基数ヒープ（単調ヒープ）
/// @details 順序基準 `Key`（符号なし整数）で最小値を取り出す。取り出した値より小さい
///          `Key` は以後 `push` できない（単調性）。Dijkstra など距離が単調増加する用途向け。
///          連続領域（`std::vector`）に値を並べる flat 実装で、`new`/`delete` を行わない。
/// @tparam Key 順序基準。符号なし整数で、最上位ビット位置によりバケットへ振り分ける。
/// @tparam Value 付随データ。`void` なら順序基準のみを格納し、`push(key)` /
///               `top() -> Key` の 1 引数 API になる。
/// @note `void` は内部で `std::monostate` に正規化し、本体を 1 つに保つ。
template <std::unsigned_integral Key = unsigned, class Value = void>
struct radix_heap {
  private:
    static constexpr bool has_value = !std::is_void_v<Value>;
    // void を保持できる型へ正規化する（メンバに持てるようにする）。
    using stored_value = std::conditional_t<has_value, Value, std::monostate>;

    // バケット数。最上位ビット位置（0..digits）に対応。
    static constexpr int bucket_count = std::numeric_limits<Key>::digits + 1;

    struct _node {
        Key key;
        [[no_unique_address]] stored_value value;
    };

  public:
    /// @brief キーの型
    /// @complexity 型別名であり実行時計算量はない
    using key_type = Key;

    /// @brief 付随値の型
    /// @complexity 型別名であり実行時計算量はない
    using value_type = Value;

    /// @brief 空の基数ヒープを構築する
    /// @complexity $O(1)$
    radix_heap() : buckets(), _last(), _size() {}

    /// @brief 要素数を返す
    /// @complexity $O(1)$
    constexpr int size() const { return _size; }

    /// @brief 空か返す
    /// @complexity $O(1)$
    constexpr bool empty() const { return _size == 0; }

    /// @brief キーと付随値を追加する
    /// @complexity 償却 $O(\log C)$
    void push(Key key, stored_value value)
    requires has_value
    {
        push_node({key, std::move(value)});
    }
    /// @brief キーを追加する
    /// @complexity 償却 $O(\log C)$
    void push(Key key)
    requires(!has_value)
    {
        push_node({key, {}});
    }
    /// @brief キーと付随値を直接構築して追加する
    /// @complexity 償却 $O(\log C)$
    template <class... Args>
    void emplace(Key key, Args &&...args) {
        push_node({key, stored_value(std::forward<Args>(args)...)});
    }

    /// @brief 最小のキーと必要なら付随値を返す
    /// @complexity 償却 $O(\log C)$
    auto top() {
        if (buckets[0].empty()) relocate();
        const _node &n = buckets[0].back();
        if constexpr (has_value) return std::pair<Key, Value>{n.key, n.value};
        else return n.key;
    }

    /// @brief 最小のキーを持つ要素を削除する
    /// @complexity 償却 $O(\log C)$
    void pop() {
        assert(_size);
        if (buckets[0].empty()) relocate();
        buckets[0].pop_back();
        --_size;
    }

  private:
    std::array<std::vector<_node>, bucket_count> buckets;
    Key _last;
    int _size;

    void push_node(_node n) {
        assert(n.key >= _last);
        ++_size;
        buckets[find_bucket(n.key ^ _last)].push_back(std::move(n));
    }

    // key（= 実値 XOR _last）が属するバケット番号。0 は _last 自身。
    static int find_bucket(Key key) { return key == 0 ? 0 : std::numeric_limits<Key>::digits - std::countl_zero(key); }

    // 最小の非空バケットを走査して新しい _last を決め、要素を撒き直す。
    void relocate() {
        int index = 1;
        while (buckets[index].empty()) ++index;
        Key new_last = buckets[index][0].key;
        for (const _node &n : buckets[index]) new_last = std::min(new_last, n.key);
        for (_node &n : buckets[index]) buckets[find_bucket(n.key ^ new_last)].push_back(std::move(n));
        _last = new_last;
        buckets[index].clear();
    }
};
