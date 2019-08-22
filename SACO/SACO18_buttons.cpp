#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll a, n, m, cnt = 0;
    cin >> a >> n >> m;

    while (m > n) {
        if (m % a == 0) {
            m /= a;
        } else {
            m++;
        }
        cnt++;
    }
    return cout << cnt + (n - m) << '\n', 0;
}