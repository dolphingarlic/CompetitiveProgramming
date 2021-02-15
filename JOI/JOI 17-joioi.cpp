/*
JOI 2017 JOIOI
- Binary search for the answer
- When we check a candidate, we just "extend" IOI's territory as much
  as possible while assuming that the maximum cell is in that territory
    - We then only need to check the maximum difference in JOI's territory
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, m, mx, grid[2000][2000], tmp[2000][2000];

void rotate() {
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        tmp[j][n - i - 1] = grid[i][j];
    swap(n, m);
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++)
        grid[i][j] = tmp[i][j];
}

bool check(int diff) {
    for (int _ : {0,0,0,0}) {
        int lmx = 0, lmn = mx, lst = m;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < lst; j++) if (grid[i][j] < mx - diff) {
                lst = j;
                break;
            }
            for (int j = lst; j < m; j++) lmx = max(lmx, grid[i][j]), lmn = min(lmn, grid[i][j]);
        }
        if (lmx - lmn <= diff) return true;
        rotate();
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
        mx = max(mx, grid[i][j]);
    }
    int l = 0, r = mx;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}