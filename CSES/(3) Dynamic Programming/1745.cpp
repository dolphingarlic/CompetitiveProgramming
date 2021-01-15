#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
bool dp[101][100001];
int a[101];
set<int> yes;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) cin >> a[i];
    dp[0][0] = true;
    FOR(i, 1, n + 1) {
        FOR(j, 0, 1000 * n + 1) {
            dp[i][j] = dp[i - 1][j] || (j >= a[i] && dp[i - 1][j - a[i]]);
            if (dp[i][j]) yes.insert(j);
        }
    }
    cout << yes.size() - 1 << '\n';
    yes.erase(0);
    for (int i : yes) cout << i << ' ';
    return 0;
}