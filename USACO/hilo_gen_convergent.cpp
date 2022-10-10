#include <iostream>
#include <random>
#include <utility>
#include <chrono>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int perm[200000], n = (tc < 2 ? 5000 : 200000);
    for (int i = 0; i < n; i++) {
        if ((i + tc) & 1) perm[i] = i / 2 + 1;
        else perm[i] = n - i / 2;
    }

    // for (int i = n - 1; i; i--) {
    //     // Shuffle 20% of the permutation
    //     if (uniform_real_distribution<double>(0, 1)(rng) < 0.8)
    //         continue;
    //     int k = rng() % i;
    //     swap(perm[i], perm[k]);
    // }

    cout << n << '\n';
    for (int i = 0; i < n; i++) cout << perm[i] << " \n"[i == n - 1];
}
