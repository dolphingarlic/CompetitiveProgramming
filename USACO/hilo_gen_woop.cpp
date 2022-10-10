#include <bits/stdc++.h>
// #include <iostream>
using namespace std;

int spaces[6] = {4, 5, 10, 20, 25, 40};

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int n = 200000, k = spaces[tc - 1], perm[200000];
    cout << n << '\n';
    for (int i = 0; i < n; i++) {
        perm[i] = i / k + n / k * (i % k) + 1;
    }
    random_shuffle(perm + n - 10000, perm + n);
    for (int i = 0; i < n; i++) cout << perm[i] << " \n"[i == n - 1];
}
