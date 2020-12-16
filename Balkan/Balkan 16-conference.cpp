/*
Balkan 2016 Conference
- Part 1: process days in reverse order and greedily invent as late as possible
- Part 2: process days in order and use DSU or something
- Part 3: process days in reverse order and keep the earliest journalist for each scientist
- Complexity: O(M)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<int, int> meet[1000001];
int latest[1000001];
pair<int, int> last_j[1000001], first_j[1000001];
bool hears[1000001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 1; i <= m; i++) cin >> meet[i].first >> meet[i].second;

    // Find the latest invention dates
    for (int i = m; i; i--) {
        int u, v;
        tie(u, v) = meet[i];
        if (u > v) swap(u, v);
        if (u <= k) {
            if (v > k) { // Scientist to journalist
                if (!latest[u]) latest[u] = i;
            } else { // Scientist to scientist
                if (latest[u] && !latest[v]) latest[v] = i;
                if (latest[v] && !latest[u]) latest[u] = i;
            }
        }
    }
    for (int i = 1; i <= k; i++) cout << (latest[i] ? latest[i] : -1) << ' ';
    cout << '\n';

    // Find the journalists who find out about inventions
    for (int i = 1; i <= m; i++) {
        int u, v;
        tie(u, v) = meet[i];
        if (latest[u] == i || latest[v] == i) hears[u] = hears[v] = true;
        else hears[u] |= hears[v], hears[v] |= hears[u];
    }
    cout << accumulate(hears + k + 1, hears + n + 1, 0) << ' ';
    for (int i = k + 1; i <= n; i++) if (hears[i]) cout << i << ' ';
    cout << '\n';

    // Find the first journalists to find out about inventions
    for (int i = 1; i <= k; i++) first_j[i] = last_j[i] = {INT_MAX, INT_MAX};
    for (int i = m; i; i--) {
        int u, v;
        tie(u, v) = meet[i];
        if (u > v) swap(u, v);
        if (u <= k) {
            if (v > k) {
                last_j[u] = {i, v};
                if (latest[u] == i) first_j[u] = last_j[u];
            } else {
                if (latest[u] <= i) first_j[u] = min(first_j[u], last_j[v]);
                if (latest[v] <= i) first_j[v] = min(first_j[v], last_j[u]);
                last_j[u] = last_j[v] = min(last_j[u], last_j[v]);
            }
        }
    }
    for (int i = 1; i <= k; i++)
        cout << (first_j[i].second != INT_MAX ? first_j[i].second : -1) << ' ';
    return 0;
}