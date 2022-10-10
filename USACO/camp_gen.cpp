// #include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int mx_t, mn_t, mx_k, mn_k;
    if (tc <= 4) {
        mx_t = 25, mn_t = 2;
        mx_k = 100, mn_k = 1;
    } else if (tc <= 7) {
        mx_t = 1000, mn_t = 500;
        mx_k = 1000000, mn_k = 500000;
    } else {
        mx_t = 1000, mn_t = 500;
        mx_k = 1000000000, mn_k = 900000000;
    }
    cout << rng() % (mx_t - mn_t + 1) + mn_t << ' ' << rng() % (mx_k - mn_k + 1) + mn_k << '\n';
}
