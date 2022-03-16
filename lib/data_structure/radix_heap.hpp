#include "template/template.hpp"

template <class Key, class Value>
struct radix_heap {
  private:
    struct _node {
        using pointer = _node*;
        Key key;
        Value value;
        int index;

        constexpr _node(Key _key, Value _value) : key(_key), value(_value), index() {}
        constexpr _node(Key _key, Value _value, int _index)
            : key(_key), value(_value), index(_index) {}

        constexpr bool operator<(const _node& rhs) const { return this->value < rhs.value; }

        constexpr auto get_pair() const { return make_pair(key, value); }
    };

  public:
    using node_pointer = typename _node::pointer;

    radix_heap() : v{}, _last(), _size() {}

    constexpr int size() const { return this->_size; }
    constexpr bool empty() const { return this->_size == 0; }

    auto push(Key key, Value value) {
        assert(value >= this->_last);
        ++this->_size;
        auto node = new _node(key, value, this->find_bucket(value ^ this->_last));
        this->v[node->index].emplace(node);
        return node;
    }
    auto emplace(Key key, Value value) { return this->push(key, value); }

    auto top() {
        if (this->v[0].empty()) this->relocate();
        return (*this->v[0].begin())->get_pair();
    }

    void pop() {
        assert(this->_size);
        if (this->v[0].empty()) this->relocate();
        this->v[0].erase(this->v[0].begin());
        --this->_size;
    }

    void update(node_pointer node, Value value) {
        if (value < node->value)
            node->value = value;
        else
            return;
        this->v[node->index].erase(node);
        node->index = this->find_bucket(value ^ this->_last);
        this->v[this->find_bucket(value ^ this->_last)].emplace(node);
    }

  private:
    std::unordered_set<node_pointer> v[std::numeric_limits<Value>::digits + 1];
    Value _last;
    int _size;

    int find_bucket(Value value) const {
        return value == 0 ? 0 : std::numeric_limits<Value>::digits - this->clz(value);
    }

    template <class U>
    int clz(U x) const {
        static_assert(std::is_integral_v<U>);
        if constexpr (std::is_signed_v<U>)
            return this->clz_unsigned(std::make_unsigned_t<U>(x)) - 1;
        else
            return this->clz_unsigned(x);
    }

    template <class U>
    int clz_unsigned(U x) const {
        static_assert(std::is_integral_v<U> && std::is_unsigned_v<U>);
        if constexpr (std::is_same_v<U, unsigned int>)
            return __builtin_clz(x);
        else if constexpr (std::is_same_v<U, unsigned long>)
            return __builtin_clzl(x);
        else if constexpr (std::is_same_v<U, unsigned long long>)
            return __builtin_clzll(x);
        else
            return -1;
    }

    void relocate() {
        int index = 1;
        while (v[index].empty()) ++index;
        auto new_last = (*std::min_element(this->v[index].begin(), this->v[index].end(),
                                           [](const auto& a, const auto& b) {
                                               return a->value < b->value;
                                           }))
                            ->value;
        for (auto node : this->v[index]) {
            node->index = this->find_bucket(node->value ^ new_last);
            this->v[this->find_bucket(node->value ^ new_last)].emplace(node);
        }
        this->_last = new_last;
        this->v[index].clear();
    }
};

template <class T>
struct radix_heap<void, T> {
    radix_heap() : v{}, _last(), _size() {}

    constexpr int size() const { return this->_size; }
    constexpr bool empty() const { return this->_size == 0; }

    void push(T x) {
        assert(x >= this->_last);
        ++this->_size;
        this->v[this->find_bucket(x ^ this->_last)].emplace_back(x);
    }
    void emplace(T x) { this->push(x); }

    T top() {
        if (this->v[0].empty()) this->relocate();
        return this->_last;
    }

    void pop() {
        assert(this->_size);
        if (this->v[0].empty()) this->relocate();
        this->v[0].pop_back();
        --this->_size;
    }

  private:
    std::vector<T> v[std::numeric_limits<T>::digits + 1];
    T _last;
    int _size;

    int find_bucket(T x) const {
        return x == 0 ? 0 : std::numeric_limits<T>::digits - this->clz(x);
    }

    template <class U>
    int clz(U x) const {
        static_assert(std::is_integral_v<U>);
        if constexpr (std::is_signed_v<U>)
            return this->clz_unsigned(std::make_unsigned_t<U>(x)) - 1;
        else
            return this->clz_unsigned(x);
    }

    template <class U>
    int clz_unsigned(U x) const {
        static_assert(std::is_integral_v<U> && std::is_unsigned_v<U>);
        if constexpr (std::is_same_v<U, unsigned int>)
            return __builtin_clz(x);
        else if constexpr (std::is_same_v<U, unsigned long>)
            return __builtin_clzl(x);
        else if constexpr (std::is_same_v<U, unsigned long long>)
            return __builtin_clzll(x);
        else
            return -1;
    }

    void relocate() {
        int index = 1;
        while (v[index].empty()) ++index;
        auto new_last = *min_element(this->v[index].begin(), this->v[index].end());
        for (auto x : this->v[index]) { this->v[this->find_bucket(x ^ new_last)].emplace_back(x); }
        this->_last = new_last;
        this->v[index].clear();
    }
};
