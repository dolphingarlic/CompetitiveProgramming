// #include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

vector<int> tree[100001];
int sz[100001];

void gen_tree(int node = 0, int x = 0) {
    int prv = 0;
    for (int i : tree[node]) {
        cout << 2 * prv + x + 1 << ' ' << 2 * prv + x + 1 << ' ';
        cout << 2 * (prv + sz[i]) + x << ' ' << 2 * (prv + sz[i]) + x << '\n';
        gen_tree(i, 2 * prv + x + 1);
        prv += sz[i];
    }
}

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int n = 100000;
    cout << n << ' ' << 2 << '\n';
    for (int i = 1; i <= n; i++) {
        int p = i - 1 - rng() % min(10, i);
        tree[p].push_back(i);
    }
    for (int i = n; i; i--) {
        sz[i]++;
        for (int j : tree[i]) sz[i] += sz[j];
    }
    gen_tree(0);
}
