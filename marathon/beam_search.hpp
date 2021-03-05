#include "marathon/_base.hpp"

constexpr int N = 1000;
constexpr int H = 125;
constexpr int W = 8;

constexpr int BEAM_SIZE = 100;

struct beam_search {
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
        priority_queue<State> cur, nxt;
        cur.push(State());
        for (int t = 0; t < N; ++t) {
            while (!nxt.empty()) nxt.pop();
            while (!cur.empty()) {
                State now = cur.top();
                cur.pop();
                for (int col = 0; col < W; ++col) {
                    State s = now.place(t, col);
                    if (nxt.size() < BEAM_SIZE || s.eval() > nxt.top().eval())
                        nxt.push(s);
                    if (nxt.size() > BEAM_SIZE) nxt.pop();
                }
            }
            swap(cur, nxt);
        }

        while (cur.size() > 1) cur.pop();

        cerr << cur.top().eval() << endl;
        return cur.top().answer();
    }
};
