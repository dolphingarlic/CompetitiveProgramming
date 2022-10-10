#include <bits/stdc++.h>
// #include <iostream>
// #include <random>
// #include <utility>
// #include <chrono>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int n = 100, max_h = 1000;

    if (tc <= 4) n = 6, max_h = 10;
    else if (tc <= 10) n = 50, max_h = 100;
    n -= tc % 2;

    cout << n << '\n';
    if (tc == 9 || tc == 10 || tc == 19 || tc == 20) {
        for (int i = 0; i < n; i++) cout << max_h << " \n"[i == n - 1];
    } else {
        cout << max_h << ' ';
        for (int i = 1; i < n; i++)
            cout << rng() % (max_h / 2) + max_h / 2 << " \n"[i == n - 1];
    }
}
