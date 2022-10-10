// #include <bits/stdc++.h>
#include <iostream>
using namespace std;
 
int main(int argc, char* argv[]) {
    int tc = atoi(argv[1]);
    // int b = atoi(argv[2]);
    // int c = atoi(argv[3]);
 
    int n = (tc < 2 ? 5000 : 200000);
    cout << n << '\n';
    for (int i = 1; i <= n; i++) {
        if (i <= n / 2) cout << i * 2 << ' ';
        else cout << 2 * (n - i) + 1 << " \n"[i == n];
    }
}
