#pragma once
#include <array>
#include <bit>
#include <cassert>
#include <concepts>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

/// @brief 基数ヒープ（単調ヒープ）
/// @details 順序基準 `Key`（符号なし整数）で最小値を取り出す。取り出した値より小さい
///          `Key` は以後 `push` できない（単調性）。Dijkstra など距離が単調増加する用途向け。
///          連続領域（`std::vector`）に値を並べる flat 実装で、`new`/`delete` を行わない。
/// @tparam Key 順序基準。符号なし整数で、最上位ビット位置によりバケットへ振り分ける。
/// @tparam Value 付随データ。`void` なら順序基準のみを格納する。
template <std::unsigned_integral Key = unsigned, class Value = void>
struct radix_heap {
  private:
    // バケット数。最上位ビット位置（0..digits）に対応。
    static constexpr int bucket_count = std::numeric_limits<Key>::digits + 1;

    struct _node {
        Key key;
        Value value;
    };

  public:
    using key_type = Key;
    using value_type = Value;

    radix_heap() : buckets(), _last(), _size() {}

    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }

    void push(Key key, Value value) {
        assert(key >= _last);
        ++_size;
        buckets[find_bucket(key ^ _last)].push_back({key, std::move(value)});
    }
    void emplace(Key key, Value value) { push(key, std::move(value)); }

    std::pair<Key, Value> top() {
        if (buckets[0].empty()) relocate();
        const _node &n = buckets[0].back();
        return {n.key, n.value};
    }

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

    // key（= 実値 XOR _last）が属するバケット番号。0 は _last 自身。
    static int find_bucket(Key key) { return key == 0 ? 0 : std::numeric_limits<Key>::digits - std::countl_zero(key); }

    // 最小の非空バケットを走査して新しい _last を決め、要素を撒き直す。
    void relocate() {
        int index = 1;
        while (buckets[index].empty()) ++index;
        Key new_last = buckets[index][0].key;
        for (const _node &n : buckets[index]) new_last = std::min(new_last, n.key);
        for (_node &n : buckets[index]) { buckets[find_bucket(n.key ^ new_last)].push_back(std::move(n)); }
        _last = new_last;
        buckets[index].clear();
    }
};

/// @brief 順序基準のみを保持する基数ヒープ
template <std::unsigned_integral T>
struct radix_heap<T, void> {
  private:
    static constexpr int bucket_count = std::numeric_limits<T>::digits + 1;

  public:
    using key_type = T;
    using value_type = void;

    radix_heap() : buckets(), _last(), _size() {}

    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }

    void push(T x) {
        assert(x >= _last);
        ++_size;
        buckets[find_bucket(x ^ _last)].push_back(x);
    }
    void emplace(T x) { push(x); }

    T top() {
        if (buckets[0].empty()) relocate();
        return _last;
    }

    void pop() {
        assert(_size);
        if (buckets[0].empty()) relocate();
        buckets[0].pop_back();
        --_size;
    }

  private:
    std::array<std::vector<T>, bucket_count> buckets;
    T _last;
    int _size;

    static int find_bucket(T x) { return x == 0 ? 0 : std::numeric_limits<T>::digits - std::countl_zero(x); }

    void relocate() {
        int index = 1;
        while (buckets[index].empty()) ++index;
        T new_last = buckets[index][0];
        for (T x : buckets[index]) new_last = std::min(new_last, x);
        for (T x : buckets[index]) buckets[find_bucket(x ^ new_last)].push_back(x);
        _last = new_last;
        buckets[index].clear();
    }
};
