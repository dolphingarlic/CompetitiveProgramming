#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bool open[1002][1002];
int n, m, visited[1002][1002], to_wall[1002][1002];
pair<int, int> graph[1002][1002][8], src, dest;

inline bool has_wall(int x, int y) {
    return !(open[x - 1][y] && open[x + 1][y] && open[x][y - 1] &&
             open[x][y + 1]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        char c;
        cin >> c;
        if (c != '#') open[i][j] = true;
        if (c == 'S') src = {i, j};
        if (c == 'C') dest = {i, j};
    }

    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        if (open[i - 1][j]) graph[i][j][0] = {i - 1, j};
        if (open[i + 1][j]) graph[i][j][1] = {i + 1, j};
        if (open[i][j - 1]) graph[i][j][2] = {i, j - 1};
        if (open[i][j + 1]) graph[i][j][3] = {i, j + 1};
    }

    queue<pair<int, int>> q;
    FOR(i, 1, n + 1) FOR(j, 1, m + 1) {
        if (open[i][j] && has_wall(i, j)) {
            to_wall[i][j] = 1;
            q.push({i, j});
        }
    }
    while (q.size()) {
        pair<int, int> curr = q.front();
        int x = curr.first, y = curr.second;
        q.pop();
        FOR(i, 0, 4) {
            if (!to_wall[graph[x][y][i].first][graph[x][y][i].second]) {
                to_wall[graph[x][y][i].first][graph[x][y][i].second] =
                    to_wall[x][y] + 1;
                q.push(graph[x][y][i]);
            }
        }
    }

    bool has = false;
    FOR(i, 0, n + 1) FOR(j, 0, m + 1) {
        if (!open[i][j])
            has = false;
        else {
            if (!has)
                graph[i][j][4] = {i, j};
            else
                graph[i][j][4] = graph[i][j - 1][4];
            has = true;
        }
    }
    FOR(j, 0, m + 1) FOR(i, 0, n + 1) {
        if (!open[i][j])
            has = false;
        else {
            if (!has)
                graph[i][j][5] = {i, j};
            else
                graph[i][j][5] = graph[i - 1][j][5];
            has = true;
        }
    }
    for (int i = n + 1; i; i--)
        for (int j = m + 1; j; j--) {
            if (!open[i][j])
                has = false;
            else {
                if (!has)
                    graph[i][j][6] = {i, j};
                else
                    graph[i][j][6] = graph[i][j + 1][6];
                has = true;
            }
        }
    for (int j = m + 1; j; j--)
        for (int i = n + 1; i; i--) {
            if (!open[i][j])
                has = false;
            else {
                if (!has)
                    graph[i][j][7] = {i, j};
                else
                    graph[i][j][7] = graph[i + 1][j][7];
                has = true;
            }
        }

    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({-1, src});
    while (pq.size()) {
        pair<int, int> curr = pq.top().second;
        int dist = pq.top().first, x = curr.first, y = curr.second;
        pq.pop();
        if (!visited[x][y]) {
            visited[x][y] = -dist;
            FOR(i, 0, 4)
            if (graph[x][y][i].first &&
                !visited[graph[x][y][i].first][graph[x][y][i].second])
                pq.push({dist - 1, graph[x][y][i]});
            FOR(i, 4, 8)
            if (graph[x][y][i].first &&
                !visited[graph[x][y][i].first][graph[x][y][i].second])
                pq.push({dist - to_wall[x][y], graph[x][y][i]});
        }
        if (curr == dest) break;
    }
    cout << visited[dest.first][dest.second] - 1;
    return 0;
}