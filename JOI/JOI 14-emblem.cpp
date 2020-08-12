#include <bits/stdc++.h>
using namespace std;

char opt[3]{'J', 'O', 'I'};
string grid[1000], emblem[2];
map<string, int> cnt;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];
    for (int i = 1; i < n; i++) for (int j = 1; j < m; j++) {
        cnt[grid[i - 1].substr(j - 1, 2) + grid[i].substr(j - 1, 2)]++;
    }
    cin >> emblem[0] >> emblem[1];
    int ans = 0;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        for (int k = 0; k < 3; k++) {
            if (i && j) cnt[grid[i - 1].substr(j - 1, 2) + grid[i].substr(j - 1, 2)]--;
            if (i && j < m - 1) cnt[grid[i - 1].substr(j, 2) + grid[i].substr(j, 2)]--;
            if (i < n - 1 && j) cnt[grid[i].substr(j - 1, 2) + grid[i + 1].substr(j - 1, 2)]--;
            if (i < n - 1 && j < m - 1) cnt[grid[i].substr(j, 2) + grid[i + 1].substr(j, 2)]--;
            char tmp = grid[i][j];
            grid[i][j] = opt[k];
            if (i && j) cnt[grid[i - 1].substr(j - 1, 2) + grid[i].substr(j - 1, 2)]++;
            if (i && j < m - 1) cnt[grid[i - 1].substr(j, 2) + grid[i].substr(j, 2)]++;
            if (i < n - 1 && j) cnt[grid[i].substr(j - 1, 2) + grid[i + 1].substr(j - 1, 2)]++;
            if (i < n - 1 && j < m - 1) cnt[grid[i].substr(j, 2) + grid[i + 1].substr(j, 2)]++;
            ans = max(ans, cnt[emblem[0] + emblem[1]]);
            if (i && j) cnt[grid[i - 1].substr(j - 1, 2) + grid[i].substr(j - 1, 2)]--;
            if (i && j < m - 1) cnt[grid[i - 1].substr(j, 2) + grid[i].substr(j, 2)]--;
            if (i < n - 1 && j) cnt[grid[i].substr(j - 1, 2) + grid[i + 1].substr(j - 1, 2)]--;
            if (i < n - 1 && j < m - 1) cnt[grid[i].substr(j, 2) + grid[i + 1].substr(j, 2)]--;
            grid[i][j] = tmp;
            if (i && j) cnt[grid[i - 1].substr(j - 1, 2) + grid[i].substr(j - 1, 2)]++;
            if (i && j < m - 1) cnt[grid[i - 1].substr(j, 2) + grid[i].substr(j, 2)]++;
            if (i < n - 1 && j) cnt[grid[i].substr(j - 1, 2) + grid[i + 1].substr(j - 1, 2)]++;
            if (i < n - 1 && j < m - 1) cnt[grid[i].substr(j, 2) + grid[i + 1].substr(j, 2)]++;
        }
    }
    cout << ans << '\n';
    return 0;
}