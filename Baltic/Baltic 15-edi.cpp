/*
Baltic 2015 Editor
- Firstly, the last operation is always active
- Secondly, if operation y can't undo x but operation z can
  undo x where x < y < z, then z can undo y
    - This means for each operation, we only care about the
      most recent operation whose level is strictly less than
      the current operation
    - View the sequence as a tree now
        - Connect each operation to the other operation
          mentioned above
        - This means we can use binary lifting to find which
          operation to undo by also storing suffix minimums
- Thirdly, if we view the sequence of numbers we get as a trie,
  each operation moves us either up or down a single node
    - This means only the current letter can be undone
    - So if we undo operation x with operation y, the answer
      for operation y is the answer for operation x - 1
        - Operation x - 1 must be active after operation y,
          so connect y with x - 1
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int anc[300001][20], mn[300001][20], ans[300001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        if (x > 0) {
            ans[i] = x;
            anc[i][0] = i;
        } else {
            x = -x;
            int curr = i - 1;
            for (int j = 19; ~j; j--) if (mn[curr][j] >= x) curr = anc[curr][j];
            anc[i][0] = curr - 1;
            ans[i] = ans[curr - 1];
            mn[i][0] = x;
            FOR(j, 1, 20) {
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
                mn[i][j] = min(mn[i][j - 1], mn[anc[i][j - 1]][j - 1]);
            }
        }
    }
    FOR(i, 1, n + 1) cout << ans[i] << '\n';
    return 0;
}