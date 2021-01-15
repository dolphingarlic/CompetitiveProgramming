#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, a[500000];
    cin >> n;
    FOR(i, 0, n - 1) {
        cin >> a[i];
    }
    sort(a, a + n - 1);
    FOR(i, 0, n - 1) {
        if (a[i] != i + 1) {
            return cout << i + 1 << '\n', 0;
        }
    }
    cout << n << '\n';
    return 0;
}