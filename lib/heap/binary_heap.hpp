#include "template/template.hpp"

/**
 * @brief 二分ヒープ
 *
 * @tparam Key キーの型
 * @tparam Value 値の型
 * @tparam Comp 比較オブジェクト
 */
template <class Key, class Value, class Comp = std::less<>>
struct binary_heap {
  private:
    struct _node {
        using pointer = _node *;

        Key key;
        Value value;
        int index;

        constexpr _node(Key _key, Value _value) : key(_key), value(_value), index() {}

        constexpr bool operator<(const _node &rhs) const { return value < rhs.value; }

        constexpr std::pair<Key, Value> get_pair() const { return std::make_pair(key, value); }
        constexpr int get_index() const { return index; }
        constexpr void set_index(int new_index) { index = new_index; }
    };

  public:
    using node_pointer = typename _node::pointer;

    binary_heap() : _size(), nodes(1), comp() {}

    std::pair<Key, Value> top() const { return nodes[1]->get_pair(); }
    constexpr int size() const { return _size; }
    constexpr bool empty() const { return size() == 0; }

    node_pointer push(Key key, Value value) {
        auto node = new _node(key, value);
        nodes.emplace_back(node);

        int index = increment_size();
        while (index > 1 && comp(nodes[index >> 1]->value, nodes[index]->value)) {
            std::swap(nodes[index], nodes[index >> 1]);
            nodes[index]->set_index(index);
            index >>= 1;
        }
        nodes[index]->set_index(index);

        return node;
    }
    node_pointer emplace(Key key, Value value) { return push(key, value); }

    void pop() {
        nodes[1] = nodes[decrement_size()];
        nodes.pop_back();

        int index = 1 << 1;
        while (index <= size()) {
            if (index < size() && comp(nodes[index]->value, nodes[index + 1]->value)) ++index;
            if (comp(nodes[index]->value, nodes[index >> 1]->value)) break;
            std::swap(nodes[index >> 1], nodes[index]);
            nodes[index >> 1]->set_index(index >> 1);
            index <<= 1;
        }
        nodes[index >> 1]->set_index(index >> 1);
    }

    void update(node_pointer node, Value value) {
        if (comp(node->value, value)) node->value = value;
        else return;
        int index = node->get_index();
        while (index > 1 && comp(nodes[index >> 1]->value, nodes[index]->value)) {
            std::swap(nodes[index], nodes[index >> 1]);
            nodes[index]->set_index(index);
            index >>= 1;
        }
        nodes[index]->set_index(index);
    }

  private:
    int _size;
    std::vector<node_pointer> nodes;
    Comp comp;

    constexpr int increment_size() { return ++(_size); }
    constexpr int decrement_size() { return (_size)--; }
};
