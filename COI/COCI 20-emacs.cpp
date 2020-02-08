/*
COCI 2020 Emacs
- Since the rectangles don't touch each other, every cell
  where its left and top neighbours aren't '*', is the top left
  corner of some rectangle
- Complexity: O(MN)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

char grid[101][101];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m, ans = 0;
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        cin >> grid[i][j];
        if (grid[i][j] == '*' && grid[i - 1][j] != '*' && grid[i][j - 1] != '*') ans++;
    }
    cout << ans;
    return 0;
}