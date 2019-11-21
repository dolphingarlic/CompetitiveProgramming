#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

int visited[2][501][501];
vector<pair<int, pair<int, int>>> graph[501][501];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    pair<int, int> src, dest;
    cin >> n >> m >> src.y >> src.x >> dest.y >> dest.x;
    FOR(i, 0, 2 * m + 1) {
        if (i & 1) {
            FOR(j, 0, 2 * n + 1) {
                char c;
                cin >> c;
                if (c == 'b') {
                    graph[i / 2][j / 2 + (j & 1)].push_back(
                        {0, {i / 2 + 1, (j + 1) / 2 + ((j + 1) & 1) - 1}});
                    graph[i / 2 + 1][(j + 1) / 2 + ((j + 1) & 1) - 1].push_back(
                        {0, {i / 2, j / 2 + (j & 1)}});
                }
                if (c == 'w') {
                    graph[i / 2][j / 2 + (j & 1)].push_back(
                        {1, {i / 2 + 1, (j + 1) / 2 + ((j + 1) & 1) - 1}});
                    graph[i / 2 + 1][(j + 1) / 2 + ((j + 1) & 1) - 1].push_back(
                        {1, {i / 2, j / 2 + (j & 1)}});
                }
            }
        } else {
            FOR(j, 0, n) {
                char c;
                cin >> c;
                if (c == 'b') {
                    graph[i / 2][j].push_back({0, {i / 2, j + 1}});
                    graph[i / 2][j + 1].push_back({0, {i / 2, j}});
                }
                if (c == 'w') {
                    graph[i / 2][j].push_back({1, {i / 2, j + 1}});
                    graph[i / 2][j + 1].push_back({1, {i / 2, j}});
                }
            }
        }
    }

    FOR(i, 0, m + 1) FOR(j, 0, n + 1) visited[0][i][j] = visited[1][i][j] = INT_MAX;

    queue<pair<pair<int, int>, pair<int, int>>> q;
    q.push({{0, 0}, src});
    q.push({{0, 1}, src});
    visited[0][src.x][src.y] = visited[1][src.x][src.y] = 0;
    while (q.size()) {
        pair<int, int> info, loc;
        tie(info, loc) = q.front();
        q.pop();

        for (auto& i : graph[loc.x][loc.y]) {
            if ((i.x ^ info.y) && visited[1 - info.y][i.y.x][i.y.y] == INT_MAX) {
                visited[1 - info.y][i.y.x][i.y.y] = info.x + 1;
                q.push({{info.x + 1, 1 - info.y}, i.y});
            }
        }
    }

    cout << min(visited[0][dest.x][dest.y], visited[1][dest.x][dest.y]);
    return 0;
}