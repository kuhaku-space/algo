#include <algorithm>
#include <cassert>
#include <limits>
#include <type_traits>
#include <unordered_set>
#include <vector>

template <class Key, class Value = void>
struct radix_heap {
  private:
    struct _node {
        using pointer = _node *;
        Key key;
        Value value;
        int index;

        constexpr _node(Key _key, Value _value) : key(_key), value(_value), index() {}
        constexpr _node(Key _key, Value _value, int _index)
            : key(_key), value(_value), index(_index) {}

        constexpr bool operator<(const _node &rhs) const { return value < rhs.value; }

        constexpr auto get_pair() const { return std::make_pair(key, value); }
    };

  public:
    using key_type = Key;
    using value_type = Value;
    using node_ptr = typename _node::pointer;

    radix_heap() : data{}, _last(), _size() {}

    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }

    auto push(Key key, Value value) {
        assert(value >= _last);
        ++_size;
        auto node = new _node(key, value, find_bucket(value ^ _last));
        data[node->index].emplace(node);
        return node;
    }
    auto emplace(Key key, Value value) { return push(key, value); }

    auto top() {
        if (data[0].empty()) relocate();
        return (*data[0].begin())->get_pair();
    }

    void pop() {
        assert(_size);
        if (data[0].empty()) relocate();
        data[0].erase(data[0].begin());
        --_size;
    }

    void update(node_ptr node, Value value) {
        if (value < node->value) node->value = value;
        else return;
        data[node->index].erase(node);
        node->index = find_bucket(value ^ _last);
        data[find_bucket(value ^ _last)].emplace(node);
    }

  private:
    std::unordered_set<node_ptr> data[std::numeric_limits<Value>::digits + 1];
    Value _last;
    int _size;

    int find_bucket(Value value) const {
        return value == 0 ? 0 : std::numeric_limits<Value>::digits - clz(value);
    }

    template <class U>
    int clz(U x) const {
        static_assert(std::is_integral_v<U>);
        if constexpr (std::is_signed_v<U>) return clz_unsigned(std::make_unsigned_t<U>(x)) - 1;
        else return clz_unsigned(x);
    }

    template <class U>
    int clz_unsigned(U x) const {
        static_assert(std::is_integral_v<U> && std::is_unsigned_v<U>);
        if constexpr (std::is_same_v<U, unsigned int>) return __builtin_clz(x);
        else if constexpr (std::is_same_v<U, unsigned long>) return __builtin_clzl(x);
        else if constexpr (std::is_same_v<U, unsigned long long>) return __builtin_clzll(x);
        else return -1;
    }

    void relocate() {
        int index = 1;
        while (data[index].empty()) ++index;
        auto new_last =
            (*std::min_element(data[index].begin(), data[index].end(),
                               [](const auto &a, const auto &b) { return a->value < b->value; }))
                ->value;
        for (auto node : data[index]) {
            node->index = find_bucket(node->value ^ new_last);
            data[find_bucket(node->value ^ new_last)].emplace(node);
        }
        _last = new_last;
        data[index].clear();
    }
};

template <class T>
struct radix_heap<T, void> {
    radix_heap() : data{}, _last(), _size() {}

    constexpr int size() const { return _size; }
    constexpr bool empty() const { return _size == 0; }

    void push(T x) {
        assert(x >= _last);
        ++_size;
        data[find_bucket(x ^ _last)].emplace_back(x);
    }
    void emplace(T x) { push(x); }

    T top() {
        if (data[0].empty()) relocate();
        return _last;
    }

    void pop() {
        assert(_size);
        if (data[0].empty()) relocate();
        data[0].pop_back();
        --_size;
    }

  private:
    std::vector<T> data[std::numeric_limits<T>::digits + 1];
    T _last;
    int _size;

    int find_bucket(T x) const { return x == 0 ? 0 : std::numeric_limits<T>::digits - clz(x); }

    template <class U>
    int clz(U x) const {
        static_assert(std::is_integral_v<U>);
        if constexpr (std::is_signed_v<U>) return clz_unsigned(std::make_unsigned_t<U>(x)) - 1;
        else return clz_unsigned(x);
    }

    template <class U>
    int clz_unsigned(U x) const {
        static_assert(std::is_integral_v<U> && std::is_unsigned_v<U>);
        if constexpr (std::is_same_v<U, unsigned int>) return __builtin_clz(x);
        else if constexpr (std::is_same_v<U, unsigned long>) return __builtin_clzl(x);
        else if constexpr (std::is_same_v<U, unsigned long long>) return __builtin_clzll(x);
        else return -1;
    }

    void relocate() {
        int index = 1;
        while (data[index].empty()) ++index;
        auto new_last = *min_element(data[index].begin(), data[index].end());
        for (auto x : data[index]) { data[find_bucket(x ^ new_last)].emplace_back(x); }
        _last = new_last;
        data[index].clear();
    }
};
