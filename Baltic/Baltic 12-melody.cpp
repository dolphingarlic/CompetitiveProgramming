/*
Baltic 2012 Melody
- First, build a graph where an edge between u and v means that Linas can play u directly after v
- Then run BFS from each note to find the number of intermediate notes he must play to get from u to v
- dp[i] = Maximum number of notes Linas can play if he plays up to (and including) the i-th note
    - Notice how if note[i] == note[j] and i < j, then dp[i] < dp[j], since Linas can just
      keep playing note[i] from i to j
- For some i, for each note v, find the more recent j such that note[j] == v and Linas can go from v
  to note[i] in at most i - j seconds
    - Take the maximum of all of these and that gets you dp[i]
- Complexity: O(LN log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

string note[101];
bool adj[101][101];
int apsp[101][101], prv_note[101][101], at[100001], dp[100001], prv_pos[100001];
vector<int> occ[101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, s, g;
    cin >> n >> s >> g;
    FOR(i, 1, n + 1) cin >> note[i];
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) {
        int diff = 0;
        FOR(k, 0, s) if (note[i][k] != note[j][k]) diff++;
        adj[i][j] = (diff <= g);
    }

    FOR(i, 1, n + 1) {
        queue<int> q;
        q.push(i);
        apsp[i][i] = 1;
        prv_note[i][i] = i;
        while (q.size()) {
            int curr = q.front();
            q.pop();
            FOR(j, 1, n + 1) if (adj[curr][j] && !apsp[i][j]) {
                apsp[i][j] = apsp[i][curr] + 1;
                prv_note[i][j] = curr;
                q.push(j);
            }
        }
        FOR(j, 1, n + 1) apsp[i][j]--;
    }

    int l;
    cin >> l;
    FOR(i, 1, l + 1) {
        cin >> at[i];
        prv_pos[i] = 0;
        dp[i] = 1;
        FOR(j, 1, n + 1) {
            if (apsp[at[i]][j] == -1) continue;
            int pos = upper_bound(occ[j].begin(), occ[j].end(), i - apsp[at[i]][j]) - occ[j].begin() - 1;
            if (~pos && dp[occ[j][pos]] + 1 > dp[i]) {
                dp[i] = dp[occ[j][pos]] + 1;
                prv_pos[i] = occ[j][pos];
            }
        }
        occ[at[i]].push_back(i);
    }

    int best_pos = max_element(dp + 1, dp + l + 1) - dp;
    cout << l - dp[best_pos] << '\n';

    stack<int> seq;
    FOR(i, best_pos, l) seq.push(at[best_pos]);
    while (prv_pos[best_pos]) {
        int curr = at[best_pos], cnt = 0;
        while (prv_note[at[prv_pos[best_pos]]][curr] != curr) {
            seq.push(curr);
            cnt++;
            curr = prv_note[at[prv_pos[best_pos]]][curr];
        }
        FOR(i, cnt, best_pos - prv_pos[best_pos]) seq.push(curr);
        best_pos = prv_pos[best_pos];
    }
    FOR(i, 0, best_pos) seq.push(at[best_pos]);

    while (seq.size()) {
        cout << seq.top() << ' ';
        seq.pop();
    }
    return 0;
}