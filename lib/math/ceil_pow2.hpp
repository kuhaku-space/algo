#include "template/template.hpp"

constexpr int ceil_pow2(int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x <<= 1;
    return x;
}
