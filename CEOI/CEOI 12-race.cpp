/*
CEOI 2012 Race
- dp1[i][j][k] = The maximum length of a type 0 course using only harbours on the arc i->j clockwise.
                 If k == 1, it starts on harbour i. Otherwise it starts on harbour j
- dp2[i][j][k] = The maximum length of a type 0 course using only harbours on the arc i->j clockwise and
                 moving only clockwise/counterclocwise.
                 If k == 1, it starts on harbour i. Otherwise it starts on harbour j
- dp3[i][j][k] = max(dp1[i][i + 1 .. j][k]) or max(dp1[i .. j - 1][j][k]) depending on k
- For subtask 1, the answer is just max(dp1[i][i][0]) for some i
- For subtask 2, notice that we have 4 critical harbours A B C D such that the path is A->B->(Stuff)->C->D->(Stuff)
    - B->(Stuff)->C must be a strictly clockwise/counterclockwise path, so we use dp2
    - D->(Stuff) must either be in the arc B->D or D->A and we can use dp1 or dp3
    - Notice how if we fix B and C, the choice of A doesn't really matter as long as it's as close to C as possible
        - This is because dp3 is monotone
        - So find the closest A to C such that A->B exists find some D on the arc B->A
        - The path A->B->(Stuff)->C->D->(Stuff) will thus have length
          1 + dp2[B][C][0] + 1 + max(dp3[A][D][1], dp3[D][B][0]) or something similar depending on direction
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp1[500][500][2], dp2[500][500][2], dp3[500][500][2];
bool adj[500][500];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, t;
    cin >> n >> t;
    FOR(i, 0, n) FOR(j, 0, n) FOR(k, 0, 2) dp2[i][j][k] = -n;
    FOR(i, 0, n) {
        int v;
        cin >> v;
        while (v) {
            adj[i][v - 1] = true;
            dp2[i][v - 1][0] = dp2[v - 1][i][1] = 1;
            cin >> v;
        }
    }

    FOR(k, 1, n + 1) FOR(i, 0, n) {
        int j = (i + k) % n;
        FOR(v, 0, n) {
            if ((v > i && v < i + k) || (v > i - n && v < i + k - n)) {
                if (adj[i][v]) dp1[i][j][0] = max(dp1[i][j][0], max(dp1[v][j][0], dp1[i][v][1]) + 1);
                if (adj[j][v]) dp1[i][j][1] = max(dp1[i][j][1], max(dp1[v][j][0], dp1[i][v][1]) + 1);
                dp2[i][j][0] = max(dp2[i][j][0], dp2[i][v][0] + dp2[v][j][0]);
                dp2[i][j][1] = max(dp2[i][j][1], dp2[i][v][1] + dp2[v][j][1]);
            }
        }
        dp3[i][j][0] = max(dp3[(i + 1) % n][j][0], dp1[i][j][0]);
        dp3[i][j][1] = max(dp3[i][(j - 1 + n) % n][1], dp1[i][j][1]);
    }

    pair<int, int> ans = {0, -1};
    FOR(i, 0, n) ans = max(ans, {max(dp1[i][i][0], dp1[i][i][1]), i});
    if (t) {
        FOR(k, 1, n + 1) FOR(i, 0, n) {
            int j = (i + k) % n;
            FOR(v, i + k + 1, i + n) if (adj[v % n][i]) {
                FOR(x, v + 1, i + n) if (adj[j][x % n])
                    ans = max(ans, {dp2[i][j][0] + max(dp3[v % n][x % n][1], dp3[x % n][i][0]) + 2, v % n});
                break;
            }
            for (int v = i + n - 1; v > i + k; v--) if (adj[v % n][j]) {
                for (int x = v - 1; x > i + k; x--) if (adj[i][x % n])
                    ans = max(ans, {dp2[i][j][1] + max(dp3[x % n][v % n][0], dp3[j][x % n][1]) + 2, v % n});
                break;
            }
        }
    }
    cout << ans.first << '\n' << ans.second + 1 << '\n';
    return 0;
}