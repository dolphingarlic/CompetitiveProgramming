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
    int ans = 0;
    int pow = 5;
    while (n / pow) {
        ans += n / pow;
        pow *= 5;
    }
    cout << ans << '\n';
    return 0;
}