// #include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <utility>
#include <vector>
using namespace std;

const int INF = 1e9 - 1;
const int BINS = 20;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
binomial_distribution<int> distribution(BINS, 0.5);

int gen_coord() {
    int base = distribution(rng);
    int noise = rng() % (INF / BINS);
    return (base * (INF / BINS) + noise) % INF + 1;
}

int x[200001], y[200001];

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    
    int n;
    if (tc <= 6) n = 5000;
    else n = 200000;
    int skewness = rng() % 100;

    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        if (i != 0 && rng() % 100 < 5) {
            // 5% chance of having the same x/y coordinate as another cow
            if (rng() & 1) {
                x[i] = x[rng() % i];
                y[i] = gen_coord();
            } else {
                x[i] = gen_coord();
                y[i] = y[rng() % i];
            }
        } else {
            // We want the covariance of x and y to be non-zero so that the
            // "ellipse" is somewhat skewed
            x[i] = gen_coord();
            y[i] = gen_coord();
            if (rng() % 100 < skewness)
                x[i] = (x[i] - 1 + y[i]) % INF + 1;
        }
        cout << x[i] << ' ' << y[i] << '\n';
    }
}
