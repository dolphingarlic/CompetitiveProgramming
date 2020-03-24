#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll n;
pair<ll, ll> a, b;

ll visited[101][101];
vector<pair<ll, ll>> ds = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                           {2, 1}, {-2, 1}, {2, -1}, {-2, -1}};

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    cin >> a.second >> a.first;
    cin >> b.second >> b.first;

    FOR(i, 1, n + 1) FOR(j, 1, n + 1) visited[i][j] = 0;

    queue<pair<ll, ll>> q;
    q.push(b);
    visited[b.first][b.second] = 1;
    while (!q.empty()) {
        pair<ll, ll> curr = q.front();
        q.pop();

        for (pair<ll, ll> i : ds) {
            if (0 < curr.first + i.first && curr.first + i.first <= n &&
                0 < curr.second + i.second && curr.second + i.second <= n &&
                visited[curr.first + i.first][curr.second + i.second] == 0) {

                visited[curr.first + i.first][curr.second + i.second] =
                    visited[curr.first][curr.second] + 1;
                q.push({curr.first + i.first, curr.second + i.second});
            }
        }
    }

    FOR(i, 1, n + 1) FOR(j, 1, n + 1) visited[i][j]--;

    bool can_stalemate = false;
    ll best_stalemate = INT_MAX;
    FOR(i, a.first, n + 1) {
        if (visited[i][a.second] > -1 && visited[i][a.second] <= i - a.first) {
            if ((visited[i][a.second] - i + a.first) & 1) {
                best_stalemate = min(best_stalemate, i - a.first - 1);
                can_stalemate = true;
            } else
                return cout << "BLACK WINS\n" << i - a.first, 0;
        }
    }

    if (can_stalemate)
        cout << "STALEMATE\n" << best_stalemate;
    else
        cout << "WHITE WINS";
    return 0;
}