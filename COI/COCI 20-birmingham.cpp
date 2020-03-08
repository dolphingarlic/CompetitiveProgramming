/*
COCI 20 Birmingham
- Basically just do a BFS and binary search for the day
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
vector<ll> graph[100001];
ll visited[100001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n, m, p, k;
    cin >> n >> m >> p >> k;
    queue<ll> q;
    FOR(i, 0, p) {
        ll x;
        cin >> x;
        visited[x] = 1;
        q.push(x);
    }
    FOR(i, 0, m) {
        ll x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
 
    while (q.size()) {
        ll curr = q.front();
        q.pop();
        for (ll i : graph[curr]) if (!visited[i]) {
            visited[i] = visited[curr] + 1;
            q.push(i);
        }
    }
 
    FOR(i, 1, n + 1) {
        visited[i]--;
        ll l = 0, r = n;
        while (l != r) {
            ll mid = (l + r) / 2;
            if (visited[i] > k * mid * (mid + 1) / 2) l = mid + 1;
            else r = mid;
        }
        cout << l << ' ';
    }
    return 0;
}