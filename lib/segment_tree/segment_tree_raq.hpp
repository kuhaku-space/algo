#include "segment_tree/segment_tree.hpp"
#include "template/template.hpp"

template <class T>
struct segment_tree_range_add_range_max {
  private:
    struct Monoid {
        using value_type = std::pair<T, T>;
        static constexpr std::pair<T, T> id =
            std::make_pair(std::numeric_limits<T>::lowest() / 2, T(0));
        static constexpr std::pair<T, T> op(const std::pair<T, T> &lhs,
                                            const std::pair<T, T> &rhs) {
            return std::make_pair(std::max(lhs.first, lhs.second + rhs.first),
                                  lhs.second + rhs.second);
        }
    };

  public:
    segment_tree_range_add_range_max(int _n, T _e) : st(_n + 1, std::make_pair(_e, T(0))) {}

    void apply(int k, T val) { this->apply(k, k + 1, val); }
    void apply(int a, int b, T val) {
        auto x = this->st.get(a);
        this->st.set(a, std::make_pair(x.second + val, x.second + val));
        auto y = this->st.get(b);
        this->st.set(b, std::make_pair(y.second - val, y.second - val));
    }
    void add(int k, T val) { this->apply(k, k + 1, val); }
    void add(int a, int b, T val) { this->apply(a, b, val); }

    T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }

    T at(int k) { return this->st.prod(0, k).second; }
    T get(int k) { return this->at(k); }

  private:
    segment_tree<Monoid> st;
};

template <class T>
struct segment_tree_range_add_range_min {
  private:
    struct Monoid {
        using value_type = std::pair<T, T>;
        static constexpr std::pair<T, T> id =
            std::make_pair(std::numeric_limits<T>::max() / 2, T(0));
        static constexpr std::pair<T, T> op(const std::pair<T, T> &lhs,
                                            const std::pair<T, T> &rhs) {
            return std::make_pair(std::min(lhs.first, lhs.second + rhs.first),
                                  lhs.second + rhs.second);
        }
    };

  public:
    segment_tree_range_add_range_min(int _n, T _e) : st(_n + 1, std::make_pair(_e, T(0))) {}

    void apply(int k, T val) { this->apply(k, k + 1, val); }
    void apply(int a, int b, T val) {
        auto x = this->st.get(a);
        this->st.set(a, std::make_pair(x.second + val, x.second + val));
        auto y = this->st.get(b);
        this->st.set(b, std::make_pair(y.second - val, y.second - val));
    }
    void add(int k, T val) { this->apply(k, k + 1, val); }
    void add(int a, int b, T val) { this->apply(a, b, val); }

    T prod(int a, int b) { return this->st.prod(0, a).second + this->st.prod(a, b).first; }

    T at(int k) { return this->st.prod(0, k).second; }
    T get(int k) { return this->at(k); }

  private:
    segment_tree<Monoid> st;
};
