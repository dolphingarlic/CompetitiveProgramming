// #include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    int n = (tc < 2 ? 5000 : 200000);
    cout << n << '\n';
    for (int i = 1; i <= n; i++)
        cout << (n - i) / 2500 * 2500 + 1250 * (i & 1) + i / 2 % 1250 + 1 << " \n"[i == n];
}
