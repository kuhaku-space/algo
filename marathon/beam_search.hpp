#include "marathon/_base.hpp"

constexpr int N = 1000;
constexpr int H = 125;
constexpr int W = 8;

constexpr int BEAM_SIZE = 100;

struct beam_search {
    struct State {
        array<array<int, H>, W> board;
        int score;

        State() : board(), score() {}

        void update_score(int row) {}

        int eval() const { return score; }

        State place(int t, int col) { State res(*this); }

        array<int, N> answer() {}

        bool operator<(const State &rhs) const { return eval() < rhs.eval(); }
    };

    array<int, N> solve() {
        State initial_state;
        priority_queue<State> cur, nxt;
        cur.push(initial_state);
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

        State res;
        while (!cur.empty()) {
            if (cur.size() == 1) res = cur.top();
            cur.pop();
        }
        cerr << res.eval() << endl;
        return res.answer();
    }
};
