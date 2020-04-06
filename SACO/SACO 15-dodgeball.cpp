#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int n, k, L;
int a[500];
int ans = 0;

void dfs(int l, int r, int time) {
    ans = max(ans, time);
    if (time > L || (a[time] >= l && a[time] <= r)) return;

    if (l > 1) dfs(l - 1, r - 1, time + 1);
    if (r < n) dfs(l + 1, r + 1, time + 1);
    dfs(l, r, time + 1);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> k >> L;
    FOR(i, 1, L + 1) cin >> a[i];
    dfs(1, k, 0);
    dfs(2, k + 1, 0);

    if (ans > L) cout << "Complete";
    else cout << ans;
    return 0;
}