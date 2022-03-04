#include "template/template.hpp"

template <class F, class G>
struct Mo {
    Mo(int n, const F &f, const G &g)
        : add(f), del(g), width((int)sqrt(n)), nl(0), nr(0), ptr(0), contains(n) {}

    void insert(int l, int r) {
        this->left.emplace_back(l);
        this->right.emplace_back(r);
    }

    void build() {
        this->order.resize(this->left.size());
        std::iota(this->order.begin(), this->order.end(), 0);
        std::sort(this->order.begin(), this->order.end(), [&](int a, int b) {
            if (this->left[a] / this->width != this->left[b] / this->width)
                return this->left[a] < this->left[b];
            return this->right[a] < this->right[b];
        });
    }

    int process() {
        if (this->ptr == this->order.size()) return -1;
        const auto id = this->order[this->ptr];
        while (this->nl > this->left[id]) this->distribute(--this->nl);
        while (this->nr < this->right[id]) this->distribute(this->nr++);
        while (this->nl < this->left[id]) this->distribute(this->nl++);
        while (this->nr > this->right[id]) this->distribute(--this->nr);
        return this->order[this->ptr++];
    }

  private:
    std::vector<int> left, right, order;
    std::vector<bool> contains;
    int width, nl, nr, ptr;
    const F add;
    const G del;

    void distribute(int idx) {
        this->contains[idx] = !this->contains[idx];
        if (this->contains[idx])
            this->add(idx);
        else
            this->del(idx);
    }
};
