#include "marathon/_base.hpp"

struct Xorshift {
    unsigned int x, y, z, w;

    Xorshift() { x = 123456789, y = 362436069, z = 521288629, w = 88675123; }

    unsigned int operator()() {
        unsigned int t = (x ^ (x << 11));
        x = y;
        y = z;
        z = w;
        return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
    }

    double rand_d() { return (double)rand() / (1LL << 32); }
};
Xorshift xor128;
