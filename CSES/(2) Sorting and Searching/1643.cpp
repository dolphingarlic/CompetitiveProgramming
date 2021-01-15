#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    ll l_max = 0, g_max = LLONG_MIN;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        l_max = max(l_max, 0ll) + x;
        g_max = max(l_max, g_max);
    }
    cout << g_max;
    return 0;
}