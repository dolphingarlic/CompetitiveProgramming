#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int n, k;
int where[201][100001];
ll pref[100001]{0}, dp[2][100001], q[100001], l = 1, r = 1;
 
bool case1(int x, int y, int i) {
    return (dp[0][y] - dp[0][x] >=
            (pref[y] - pref[x]) * (pref[n] - pref[i]));
}
 
bool case2(int x, int y, int i) {
    return ((dp[0][y] - dp[0][x]) * (pref[i] - pref[y]) <=
            (dp[0][i] - dp[0][y]) * (pref[y] - pref[x]));
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        pref[i] = pref[i - 1] + x;
    }
 
    fill(dp[0], dp[0] + n + 1, 0);
    FOR(i, 1, k + 1) {
        q[r++] = 0;
        FOR(j, 1, n + 1) {
            while (r - l > 1 && case1(q[l], q[l + 1], j)) l++;
 
            ll x = q[l];
            dp[1][j] = dp[0][x] + (pref[j] - pref[x]) * (pref[n] - pref[j]);
            where[i][j] = x;
 
            while (r - l > 1 && case2(q[r - 2], q[r - 1], j)) r--;
            q[r++] = j;
        }
        l = r = 1;
        FOR(j, 1, n + 1) dp[0][j] = dp[1][j];
    }
 
    ll mx = -1;
    int indx = -1;
    FOR(i, 1, n + 1) {
        if (dp[0][i] > mx) mx = dp[0][i], indx = i;
    }
    cout << mx << '\n';
    FOR(i, 0, k) {
        cout << indx << ' ';
        indx = where[k - i][indx];
    }
    cout << '\n';
    return 0;
}