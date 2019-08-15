#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct State {
    int a, b, dir;
 } dp[1001][1001][2];

int n, m;
bool graph[1001][1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    FOR(i, 0, m) {
        int a, b;
        cin >> a >> b;
        graph[a][b] = graph[b][a] = true;
    }

    FOR(i, 1, n + 1) dp[i][i][0] = dp[i][i][1] = {1, 1, -1};

    FOR(j, 1, n) {
        FOR(i, 1, n + 1) {
            int k = (i + j - 1) % n + 1;

            if (graph[i][i % n + 1] && dp[i % n + 1][k][1].a) dp[i][k][1] = {i % n + 1, k, 1};
            else if (graph[i][k] && dp[k][i % n + 1][0].a) dp[i][k][1] = {k, i % n + 1, 0};
            else dp[i][k][1] = {0, 0, 0};

            if (graph[k][(k + n - 1) % n] && dp[(k + n - 1) % n][i][0].a) dp[k][i][0] = {(k + n - 1) % n, i, 0};
            else if (graph[k][i] && dp[i][(k + n - 1) % n][1].a) dp[k][i][0] = {i, (k + n - 1) % n, 1};
            else dp[k][i][0] = {0, 0, 0};
        }
    }

    State curr = {0, 0, 0};
    FOR(i, 1, n + 1) {
        if (dp[i][i % n + 1][0].a) {
            curr = {i, i % n + 1, 0};
            break;
        } else if (dp[i][(i + n - 1) % n][1].a) {
            curr = {i, (i + n - 1) % n, 1};
            break;
        }
    }

    if (curr.a) {
        while (curr.dir != -1) {
            cout << curr.a << '\n';
            curr = dp[curr.a][curr.b][curr.dir];
        }
    } else cout << "-1\n";

    return 0;
}