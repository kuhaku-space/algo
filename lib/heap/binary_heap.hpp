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

        constexpr bool operator<(const _node &rhs) const { return this->value < rhs.value; }

        constexpr std::pair<Key, Value> get_pair() const { return std::make_pair(key, value); }
        constexpr int get_index() const { return this->index; }
        constexpr void set_index(int new_index) { this->index = new_index; }
    };

  public:
    using node_ptr = typename _node::pointer;

    binary_heap() : _size(), nodes(1), comp() {}

    std::pair<Key, Value> top() const { return this->nodes[1]->get_pair(); }
    constexpr int size() const { return this->_size; }
    constexpr bool empty() const { return this->size() == 0; }

    node_ptr push(Key key, Value value) {
        auto node = new _node(key, value);
        this->nodes.emplace_back(node);

        int index = this->increment_size();
        while (index > 1 && comp(this->nodes[index >> 1]->value, this->nodes[index]->value)) {
            swap(this->nodes[index], this->nodes[index >> 1]);
            this->nodes[index]->set_index(index);
            index >>= 1;
        }
        this->nodes[index]->set_index(index);

        return node;
    }
    node_ptr emplace(Key key, Value value) { return this->push(key, value); }

    void pop() {
        this->nodes[1] = this->nodes[this->decrement_size()];
        this->nodes.pop_back();

        int index = 1 << 1;
        while (index <= this->size()) {
            if (index < this->size() &&
                comp(this->nodes[index]->value, this->nodes[index + 1]->value))
                ++index;
            if (comp(this->nodes[index]->value, this->nodes[index >> 1]->value)) break;
            swap(this->nodes[index >> 1], this->nodes[index]);
            this->nodes[index >> 1]->set_index(index >> 1);
            index <<= 1;
        }
        this->nodes[index >> 1]->set_index(index >> 1);
    }

    void update(node_ptr node, Value value) {
        if (comp(node->value, value)) node->value = value;
        else return;
        int index = node->get_index();
        while (index > 1 && comp(this->nodes[index >> 1]->value, this->nodes[index]->value)) {
            swap(this->nodes[index], this->nodes[index >> 1]);
            this->nodes[index]->set_index(index);
            index >>= 1;
        }
        this->nodes[index]->set_index(index);
    }

  private:
    int _size;
    std::vector<node_ptr> nodes;
    Comp comp;

    constexpr int increment_size() { return ++(this->_size); }
    constexpr int decrement_size() { return (this->_size)--; }
};
