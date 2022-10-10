// #include <bits/stdc++.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <set>
#include <utility>
#include <vector>
#include <numeric>
using namespace std;

const int INF = 1e9;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int par[100001], l[100001], r[100001];

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int max_n = 100000;
    int max_c = 100;
    int max_rng = INF;
    int b = 1;
    if (tc <= 4) {
        if (tc == 3) b = 0;
        max_rng = 1;
    } else if (tc <= 6) {
        if (tc == 5) b = 0;
        max_c = 1;
    } else {
        if (tc <= 11) b = 0;
    }

    int t = rng() % 7 + 3 + (1 - b);
    cout << t << ' ' << b << '\n';
    for (int _ = 0; _ < t; _++) {
        int n = max_n / t;
        cout << n << '\n';
        // Generate parents
        for (int i = 2; i <= n; i++) {
            par[i] = i - rng() % max_c - 1;
            if (par[i] < 1) par[i] = 1;
            cout << par[i] << " \n"[i == n];
        }
        // Generate ranges
        if (max_rng != 1 && _ < 2) {
            // First, 2 cases of nested ranges
            for (int i = 1; i <= n; i++) {
                if (i == 1) {
                    l[i] = 0;
                    r[i] = INF;
                } else {
                    l[i] = rng() % (r[par[i]] - l[par[i]] + 1) + l[par[i]];
                    r[i] = rng() % (r[par[i]] - l[par[i]] + 1) + l[par[i]];
                    if (l[i] > r[i]) swap(l[i], r[i]);
                }
                cout << l[i] << ' ' << r[i] << '\n';
            }
        } else if (max_rng == 1) {
            for (int i = 1; i <= n; i++) {
                int l = rng() % (INF + 1);
                cout << l << ' ' << l << '\n';
            }
        } else {
            // Random ranges
            for (int i = 1; i <= n; i++) {
                l[i] = rng() % (INF + 1);
                r[i] = rng() % (INF + 1);
                if (l[i] > r[i]) swap(l[i], r[i]);
                cout << l[i] << ' ' << r[i] << '\n';
            }
        }
    }
}
