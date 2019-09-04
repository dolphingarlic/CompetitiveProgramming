#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

int n, m;
pair<int, int> u, v, t;
int su[701][701], sv[701][701];
bool visited[701][701], is_water[701][701];

bool check(int i, int j, int val) {
    bool valid = true;
    for (int k = i; k < n && is_water[k][j] && valid; k++)
        valid = (sv[k][j] > val);
    for (int k = i; k > -1 && is_water[k][j] && valid; k--)
        valid = (sv[k][j] > val);
    for (int k = j; k < m && is_water[i][k] && valid; k++)
        valid = (sv[i][k] > val);
    for (int k = j; k > -1 && is_water[i][k] && valid; k--)
        valid = (sv[i][k] > val);
    return valid;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    FOR(i, 0, n) FOR(j, 0, m) {
        char c;
        cin >> c;
        if (c == 'Y') u = {i, j};
        if (c == 'V') v = {i, j};
        if (c == 'T') t = {i, j};
        if (c == 'I') is_water[i][j] = false;
        else is_water[i][j] = true;
    }

    FOR(i, 0, n) FOR(j, 0, m) sv[i][j] = 500000;

    queue<pair<int, int>> q;
    q.push(v);
    sv[v.x][v.y] = 1;
    while (!q.empty()) {
        pair<int, int> c = q.front();
        q.pop();

        if (c.x < n - 1 && is_water[c.x + 1][c.y] && sv[c.x + 1][c.y] == 500000) {
            sv[c.x + 1][c.y] = sv[c.x][c.y] + 1;
            q.push({c.x + 1, c.y});
        }
        if (c.x > 0 && is_water[c.x - 1][c.y] && sv[c.x - 1][c.y] == 500000) {
            sv[c.x - 1][c.y] = sv[c.x][c.y] + 1;
            q.push({c.x - 1, c.y});
        }
        if (c.y < m - 1 && is_water[c.x][c.y + 1] && sv[c.x][c.y + 1] == 500000) {
            sv[c.x][c.y + 1] = sv[c.x][c.y] + 1;
            q.push({c.x, c.y + 1});
        }
        if (c.y > 0 && is_water[c.x][c.y - 1] && sv[c.x][c.y - 1] == 500000) {
            sv[c.x][c.y - 1] = sv[c.x][c.y] + 1;
            q.push({c.x, c.y - 1});
        }
    }

    q.push(u);
    su[u.x][u.y] = 1;
    visited[u.x][u.y] = true;
    while (!q.empty()) {
        pair<int, int> c = q.front();
        q.pop();

        if (c == t) return cout << "YES", 0;

        if (c.x < n - 1 && is_water[c.x + 1][c.y] && !visited[c.x + 1][c.y] && check(c.x + 1, c.y, su[c.x][c.y] + 1)) {
            su[c.x + 1][c.y] = su[c.x][c.y] + 1;
            visited[c.x + 1][c.y] = true;
            q.push({c.x + 1, c.y});
        }
        if (c.x > 0 && is_water[c.x - 1][c.y] && !visited[c.x - 1][c.y] && check(c.x - 1, c.y, su[c.x][c.y] + 1)) {
            su[c.x - 1][c.y] = su[c.x][c.y] + 1;
            visited[c.x - 1][c.y] = true;
            q.push({c.x - 1, c.y});
        }
        if (c.y < m - 1 && is_water[c.x][c.y + 1] && !visited[c.x][c.y + 1] && check(c.x, c.y + 1, su[c.x][c.y] + 1)) {
            su[c.x][c.y + 1] = su[c.x][c.y] + 1;
            visited[c.x][c.y + 1] = true;
            q.push({c.x, c.y + 1});
        }
        if (c.y > 0 && is_water[c.x][c.y - 1] && !visited[c.x][c.y - 1] && check(c.x, c.y - 1, su[c.x][c.y] + 1)) {
            su[c.x][c.y - 1] = su[c.x][c.y] + 1;
            visited[c.x][c.y - 1] = true;
            q.push({c.x, c.y - 1});
        }
    }
    return cout << "NO", 0;
}