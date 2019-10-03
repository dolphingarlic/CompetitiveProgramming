#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
typedef long long ll;

vector<int> graph[10001];
int visited[10001][2];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    queue<int> q;
    q.push(a);
    visited[a][0] = 1;
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (int i : graph[curr]) {
            if (!visited[i][0]) {
                visited[i][0] = visited[curr][0] + 1;
                q.push(i);
            }
        }
    }
    q.push(b);
    visited[b][1] = 1;
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (int i : graph[curr]) {
            if (!visited[i][1]) {
                visited[i][1] = visited[curr][1] + 1;
                q.push(i);
            }
        }
    }

    int ans = INT_MAX, room = -1;
    FOR(i, 1, n + 1) {
        if (visited[i][0] && visited[i][1]) {
            if (ans > max(visited[i][0] - 1, visited[i][1] - 1)) ans = max(visited[i][0] - 1, visited[i][1] - 1), room = i;
        }
    }
    cout << room;
    return 0;
}