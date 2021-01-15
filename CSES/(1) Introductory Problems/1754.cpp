#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;
 
int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int a, b;
        cin >> a >> b;
        if ((a + b) % 3 == 0 && 2 * a >= b && 2 * b >= a) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}