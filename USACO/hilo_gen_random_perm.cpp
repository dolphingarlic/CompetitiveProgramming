#include <bits/stdc++.h>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count()); 

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int perm[200000], n = 200000;
    iota(perm, perm + n, 1);
    shuffle(perm, perm + n, rng);

    cout << n << '\n';
    for (int i = 0; i < n; i++) cout << perm[i] << " \n"[i == n - 1];
}
