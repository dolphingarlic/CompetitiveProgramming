#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    if (n == 2 || n == 3) {
        cout << "NO SOLUTION\n";
    } else if (n == 1) {
        cout << "1\n";
    } else if (n == 4) {
        cout << "2 4 1 3\n";
    } else {
        FOR(i, 0, n) {
            if (i & 1) {
                cout << n - i / 2 - ceil(n / 2.0) << ' ';
            } else {
                cout << n - i / 2 << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}