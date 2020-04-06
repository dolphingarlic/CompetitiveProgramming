#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int MOD = 1e6;

int graph[701][701], visited[701][2], num_paths[701][2];
bool is_cookie[701];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n;
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) cin >> graph[i][j];
    cin >> k;
    FOR(i, 0, k) {
        int x;
        cin >> x;
        is_cookie[x] = true;
    }

    memset(visited, 0x3f, sizeof(visited));
    priority_queue<tuple<int, int, int>> pq;
    pq.push({-1, 1, is_cookie[1]});
    num_paths[1][is_cookie[1]] = 1;
    visited[1][is_cookie[1]] = 1;
    while (pq.size()) {
        int cost, curr, cookie;
        tie(cost, curr, cookie) = pq.top();
        pq.pop();
        if (-cost > visited[curr][cookie]) continue;
        FOR(i, 1, n + 1) {
            if (i == curr) continue;
            if (graph[curr][i] - cost < visited[i][cookie | is_cookie[i]]) {
                num_paths[i][cookie | is_cookie[i]] = num_paths[curr][cookie];
                visited[i][cookie | is_cookie[i]] = graph[curr][i] - cost;
                pq.push({cost - graph[curr][i], i, cookie | is_cookie[i]});
            } else if (graph[curr][i] - cost == visited[i][cookie | is_cookie[i]]) {
                num_paths[i][cookie | is_cookie[i]] += num_paths[curr][cookie];
                if (num_paths[i][cookie | is_cookie[i]] >= MOD) num_paths[i][cookie | is_cookie[i]] -= MOD;
            }
        }
    }

    cout << visited[n][1] - 1 << ' ' << num_paths[n][1];
    return 0;
}