#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    while (n != 1) {
        cout << n << ' ';
        if (n & 1) {
            n *= 3;
            n++;
        } else {
            n /= 2;
        }
    }
    cout << 1 << '\n';
    return 0;
}