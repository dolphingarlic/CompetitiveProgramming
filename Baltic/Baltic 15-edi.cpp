/*
Baltic 2015 Editor
- Firstly, notice how if x can't undo y and z can't undo x, then z can't undo y.
- Let each operation be a node.
    - If undo operation x undoes operation y, draw an edge between x and y - 1 and let par[x] = y - 1.
    - Notice how the answer for x is the answer for par[x].
- Consider an undo operation z.
    - If z can't undo x, then z can't undo any operation in the range (par[x], x].
    - This is because par[x] + 1 is the most recent active operation x could undo and the states of the nodes (par[x] + 1, x] remain unchanged.
    - This still holds when we undo some operations.
- Therefore, the operation we undo must lie on some path from the most recent operation upwards.
- We can use suffix minimums and binary lifting to find this operation.
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