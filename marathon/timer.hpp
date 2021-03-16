#include "marathon/_base.hpp"

struct Timer {
    using ull = unsigned long long;
    vector<ull> at;
    vector<ull> sum;

    inline ull get_tsc() {
        ull high, low;
        __asm__ volatile("rdtsc" : "=a"(low), "=d"(high));
        return (high << 32) | low;
    }

    void start(int i) {
        if (i >= at.size()) {
            at.resize(i + 1);
            sum.resize(i + 1);
        }
        at[i] = get_tsc();
    }

    void stop(int i) { sum[i] += (get_tsc() - at[i]); }

    void print() {
        cerr << "timer:[";
        for (int i = 0; i < at.size(); ++i) {
            cerr << sum[i] << ", ";
            if (i % 10 == 9) cerr << endl;
        }
        cerr << "]" << endl;
    }
};
