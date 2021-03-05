#include "marathon/_base.hpp"
#include "marathon/xorshift.hpp"

constexpr int SZ = 26;
constexpr int D = 365;
constexpr double T0 = 5e3, T1 = 1e2, TL = 1.95;

// 焼きなまし法
struct annealing {
    double temperature(double t) {
        t /= TL;
        return pow(T0, 1.0 - t) * pow(T1, t);
    }

    int calc_score(array<char, D> arr) {
        int res = 0;
        return res;
    }

    bool is_update(int diff_score, double temp) {
        if (diff_score >= 0) return true;
        return exp((double)diff_score / temp) >= xor128.rand_d();
    }

    int solve(array<char, D> &arr) {
        int score = calc_score(arr);

        while ((double)clock() / CLOCKS_PER_SEC < TL) {
            double t = (double)clock() / CLOCKS_PER_SEC;
            double temp = temperature(t);
            for (size_t i = 0; i < 100; ++i) {
                if (xor128() % 2) {  // １点変更
                    int d = xor128() % D;
                    char e = xor128() % SZ;
                    swap(arr[d], e);
                    int new_score = calc_score(arr);
                    if (!is_update(new_score - score, temp))
                        swap(arr[d], e);
                    else
                        score = new_score;
                } else {  // ２点スワップ
                    int d1 = xor128() % (D - 1);
                    int d2 = min((int)(d1 + 1 + xor128() % 20), D - 1);
                    swap(arr[d1], arr[d2]);
                    int new_score = calc_score(arr);
                    if (!is_update(new_score - score, temp))
                        swap(arr[d2], arr[d1]);
                    else
                        score = new_score;
                }
            }
        }

        return score;
    }
};
