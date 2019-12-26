#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll dx[8]{2, 2, -2, -2, 1, 1, -1, -1}, dy[8]{1, -1, 1, -1, 2, -2, 2, -2};
ll sx[8]{3, 3, -3, -3, 1, 1, -1, -1}, sy[8]{1, -1, 1, -1, 3, -3, 3, -3};

ll r, v;
bool inside(ll a, ll b) {
    return (a > -1 && b > -1 && a < r && b < v);
}

struct Short {
    ll val;
    pair<ll, ll> last;
} visited[2][100][100];
bool forbidden[100][100];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("ratsusis.txt", "r", stdin);
    freopen("ratsuval.txt", "w", stdout);
    cin >> r >> v;
    pair<ll, ll> start, dest;
    FOR(i, 0, r) FOR(j, 0, v) {
        char c;
        cin >> c;
        if (c == '*') start = {i, j};
        else if (c == '@') dest = {i, j};
        else if (c == '#') forbidden[i][j] = true;
    }

    queue<pair<pair<ll, ll>, ll>> q;
    q.push({start, 0});
    visited[0][start.first][start.second] = {1, {-1, -1}};
    while (q.size()) {
        ll x, y, used;
        tie(x, y) = q.front().first;
        used = q.front().second;
        q.pop();

        FOR(i, 0, 8) {
            if (inside(x + dx[i], y + dy[i]) && !forbidden[x + dx[i]][y + dy[i]] && !visited[used][x + dx[i]][y + dy[i]].val) {
                visited[used][x + dx[i]][y + dy[i]] = {visited[used][x][y].val + 1, {x, y}};
                q.push({{x + dx[i], y + dy[i]}, used});
            }
        }
        if (!used) FOR(i, 0, 8) {
            if (inside(x + sx[i], y + sy[i]) && !forbidden[x + sx[i]][y + sy[i]] && !visited[1][x + sx[i]][y + sy[i]].val) {
                visited[1][x + sx[i]][y + sy[i]] = {visited[0][x][y].val + 1, {x, y}};
                q.push({{x + sx[i], y + sy[i]}, 1});
            }
        }
    }

    if (visited[1][dest.first][dest.second].val && (!visited[0][dest.first][dest.second].val || visited[0][dest.first][dest.second].val >= visited[1][dest.first][dest.second].val)) {
        ll opt = visited[1][dest.first][dest.second].val, used = 1;
        cout << opt - 1 << '\n';
        FOR(i, 0, opt) {
            cout << dest.first + 1 << ' ' << dest.second + 1 << '\n';
            pair<ll, ll> nxt = visited[used][dest.first][dest.second].last;
            if (used && abs(nxt.first - dest.first) == 3 || abs(nxt.second - dest.second) == 3) used--;
            dest = nxt;
        }
    } else {
        ll opt = visited[0][dest.first][dest.second].val;
        cout << opt - 1 << '\n';
        FOR(i, 0, opt) {
            cout << dest.first + 1 << ' ' << dest.second + 1 << '\n';
            dest = visited[0][dest.first][dest.second].last;
        }
    }
    return 0;
}