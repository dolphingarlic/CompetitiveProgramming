#include <bits/stdc++.h>
// #include <iostream>
// #include <random>
// #include <utility>
// #include <chrono>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());

int gen_n(int max_n, int tc) {
    int n = max_n - rng() % int(log2(max_n + 6));
    if (tc != 2) n -= 2;
    if (tc >= 3 && tc <= 8) {
        if (tc <= 5)
            n -= n % 2;
        else
            n -= (n - 1) % 2;
    } else if (tc >= 9 && tc <= 14) {
        if (tc <= 11)
            n -= n % 2;
        else
            n -= (n - 1) % 2;
    }
    return n;
}

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);

    int max_n = 10000;
    long long max_h = 1000000001;

    if (tc == 2)
        max_n = 3, max_h = 101;
    else if (tc <= 8)
        max_n = 100, max_h = 101;
    else if (tc <= 14)
        max_n = 100;

    int t = (tc == 15 ? 10 : 100);
    cout << t << '\n';
    if (tc == 2) {
        cout << "3\n1 0 0\n";
        t--;
    }
    if (tc >= 12) {
        // Test overflow
        int n = max_n - 1;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
            cout << (i % 2 ? max_h - 1 : max_h / 2) << " \n"[i == n - 1];
        t--;
    }
    if (tc == 15) {
        // Test O(N^3)
        int n = max_n - 1;
        cout << n << '\n';
        for (int i = 0; i < n; i++)
            cout << max_h - (i % 2) - 1 << " \n"[i == n - 1];
        t--;
    }
    while (t--) {
        int n = gen_n(max_n, tc);
        int test_type = rng() % 5;
        if (test_type == 4) {
            cout << n << '\n';
            for (int i = 0; i < n; i++)
                cout << rng() % max_h << " \n"[i == n - 1];
            continue;
        }
        int h[100000];
        long long prv = 0, mx = 0, mn = max_h;
        for (int i = 0; i < n - 1; i++) {
            long long nxt = rng() % (max_h / 2);
            h[i] = prv + nxt;
            mx = max(mx, prv + nxt);
            mn = min(mn, prv + nxt);
            prv = nxt;
        }
        mn = min(mn, prv);
        h[n - 1] = prv;
        int scaling = -(rng() % (mn + 1));
        if (test_type == 1 && tc != 2)
            scaling = 0;
        else if (test_type != 0)
            scaling = rng() % (max_h - mx);
        for (int i = 0; i < n; i++) h[i] += scaling;

        if (test_type == 1 && tc != 2)
            cout << n + 2 << '\n' << rng() % max_h << " 0 ";
        else
            cout << n << '\n';
        for (int i = 0; i < n; i++) {
            assert(h[i] < max_h);
            assert(h[i] >= 0);
            cout << h[i] << " \n"[i == n - 1];
        }
    }
}
