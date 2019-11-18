#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bool grid[1000][1000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, ans = 0;
    cin >> n;
    FOR(i, 0, n) FOR(j, 0, n) {
        cin >> grid[i][j];
        ans += grid[i][j];
    }
    FOR(k, 1, n) {
        int cnt = 0;
        FOR(i, 0, n - k) FOR(j, 0, n - k) {
            grid[i][j] = (grid[i][j] && grid[i][j + 1] && grid[i + 1][j] && grid[i + 1][j + 1]);
            cnt += grid[i][j];
        }
        if (cnt == 0) return cout << k * ans, 0;
        ans = cnt;
    }
    cout << n * ans;
    return 0;
}