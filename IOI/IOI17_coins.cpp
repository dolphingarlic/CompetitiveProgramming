#include "coins.h"

std::vector<int> coin_flips(std::vector<int> b, int c) {
    std::vector<int> flips(1);
    int xr = c;
    for (int i = 0; i < b.size(); i++) {
        xr ^= b[i] * i;
    }
    flips[0] = xr;
    return flips;
}

int find_coin(std::vector<int> b) {
    int xr = 0;
    for (int i = 0; i < b.size(); i++) {
        xr ^= b[i] * i;
    }
    return xr;
}
