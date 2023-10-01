#include <functional>
#include <utility>

/**
 * @brief leftist heap
 *
 * @tparam T 要素の型
 *
 * @see http://hos.ac/blog/#blog0001
 */
template <class T, class Comp = std::less<>>
struct leftist_heap {
  private:
    struct _node {
        using pointer = _node *;

        pointer _left, _right;
        int _rank;
        T _val;

        constexpr _node() : _left(), _right(), _rank(), _val() {}
        constexpr _node(const T &_val) : _left(), _right(), _rank(), _val(_val) {}
        constexpr _node(T &&_val) : _left(), _right(), _rank(), _val(_val) {}
        template <typename... Args>
        constexpr _node(Args &&...args)
            : _left(), _right(), _rank(), _val(std::forward<Args>(args)...) {}
    };

  public:
    using value_type = T;
    using node_pointer = typename _node::pointer;

    leftist_heap() : _root() {}

    constexpr bool empty() const { return !_root; }
    constexpr T top() const { return _root->_val; }

    constexpr void push(const T &val) {
        auto node = new _node(val);
        _root = meld(_root, node);
    }
    constexpr void push(T &&val) {
        auto node = new _node(std::move(val));
        _root = meld(_root, node);
    }
    template <typename... Args>
    constexpr void emplace(Args &&...args) {
        auto node = new _node(std::forward<Args>(args)...);
        _root = meld(_root, node);
    }

    constexpr void pop() { _root = meld(_root->_left, _root->_right); }

    constexpr void meld(const leftist_heap<T, Comp> &rhs) { _root = meld(_root, rhs._root); }

  private:
    node_pointer _root;
    Comp _comp;

    constexpr node_pointer meld(node_pointer a, node_pointer b) {
        if (!a) return b;
        if (!b) return a;
        if (_comp(a->_val, b->_val)) std::swap(a, b);
        a->_right = meld(a->_right, b);
        if (!a->_left || a->_left->_rank < a->_right->_rank) std::swap(a->_left, a->_right);
        a->_rank = (!a->_right ? 0 : a->_right->_rank) + 1;
        return a;
    }
};
