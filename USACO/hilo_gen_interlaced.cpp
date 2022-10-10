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

    int ord[200000], perm[200000], n = 100000;
    iota(perm, perm + 2 * n, 1);
    reverse(perm + n / 2, perm + n);

    iota(ord, ord + n, 1);
    shuffle(ord, ord + n, rng);
    for (int i = 0; i < n; i += 5000) {
        sort(ord + i, ord + i + 5000);
        if ((i / 5000) & 1)
            reverse(ord + i, ord + i + 5000);
    }
    for (int i = 0; i < n; i++)
        perm[n + ord[i] - 1] = n + i + 1;

    cout << 2 * n << '\n';
    for (int i = 0; i < 2 * n; i++) cout << perm[i] << " \n"[i == 2 * n - 1];
}
