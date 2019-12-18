#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, k, m;
vector<int> arr;
int ans[20], at[20];

void check() {
    // Check number of inversions
    memset(at, 0, sizeof(at));
    int inv = 0;
    for (int i : arr) {
        FOR(j, i, n) inv += at[j];
        at[i] = 1;
    }
    if (inv != k) return;

    memset(at, 0, sizeof(at));
    for (int i : arr) {
        ans[i] += at[i] + 1;
        if (ans[i] >= m) ans[i] -= m;
        for (int j = i - 1; ~j && at[j] == at[i]; j--) at[j]++;
        for (int j = i + 1; j < n && at[j] == at[i]; j++) at[j]++;
    }
}

void dfs(int curr, int mask) {
    arr.push_back(curr);
    if (mask == (1 << n) - 1) check();
    FOR(i, 0, n) if (!(mask & (1 << i))) dfs(i, mask + (1 << i));
    arr.pop_back();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // freopen("treedepth.in", "r", stdin);
    // freopen("treedepth.out", "w", stdout);
    cin >> n >> k >> m;
    for (k = 0; k <= n * (n - 1) / 2; k++) {
        fill(ans, ans + n, 0);
        FOR(i, 0, n) dfs(i, 1 << i);
        FOR(i, 0, n) cout << ans[i] << " \n"[i == n - 1];
    }
    return 0;
}