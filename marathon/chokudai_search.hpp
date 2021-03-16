#include "marathon/_base.hpp"

constexpr int N = 1000;
constexpr int H = 125;
constexpr int W = 8;

constexpr double TL = 1.9;

struct chokudai_search {
    struct State {
        int score;

        State() : score() {}

        bool operator<(const State &rhs) const { return eval() < rhs.eval(); }
        bool operator>(const State &rhs) const { return rhs < *this; }

        int eval() const { return score; }

        void update_score(int row) {}

        State place(int t, int col) {
            State res(*this);
            return res;
        }

        array<int, N> answer() const {}
    };

    array<int, N> solve() {
        vector<priority_queue<State>> v(N + 1);
        v[0].push(State());
        int t = 0;
        while ((double)clock() / CLOCKS_PER_SEC < TL) {
            if (v[t].empty()) {
                if ((++t) >= N) t = 0;
                continue;
            }
            State now = v[t].top();
            v[t].pop();
            for (int col = 0; col < W; ++col) {
                v[t + 1].push(now.place(t, col));
            }
            if ((++t) >= N) t = 0;
        }

        while (v[N].size() > 1) v[N].pop();

        cerr << v[N].top().eval() << endl;
        return v[N].top().answer();
    }
};
