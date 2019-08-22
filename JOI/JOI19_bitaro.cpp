#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
char grid[3001][3001];
ll pref1[3001][3001], pref2[3001][3001];
 
// Prefix sums
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            cin >> grid[i][j];
            pref1[i][j] = pref1[i][j - 1];
            pref2[j][i] = pref2[j][i - 1];
            if (grid[i][j] == 'O') pref1[i][j]++;
            else if (grid[i][j] == 'I') pref2[j][i]++;
        }
    }
 
    ll ans = 0;
    FOR(i, 1, n + 1) {
        FOR(j, 1, m + 1) {
            if (grid[i][j] == 'J') ans += (pref1[i][m] - pref1[i][j]) * (pref2[j][n] - pref2[j][i]);
        }
    }
    cout << ans << '\n';
    return 0;
}