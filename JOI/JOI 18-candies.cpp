/*
JOISC 2018 Candies
- Literally just APIO 2007 Backup but max instead of min
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    int l, r;
    ll cost;
};
bool operator<(Edge A, Edge B) { return A.l < B.l; }
bool operator>(Edge A, Edge B) { return A.cost < B.cost; }

Edge merge(Edge A, Edge B, Edge C) { return {A.l, C.r, A.cost + C.cost - B.cost}; }

bool visited[200001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n;

    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    set<Edge> edges;
    for (int i = 1; i <= n; i++) {
        ll a;
        cin >> a;
        Edge e = {i, i + 1, a};
        pq.push(e);
        edges.insert(e);
    }
    Edge e = {n + 1, n + 2, (ll)-1e14};
    pq.push(e);
    edges.insert(e);
    e = {0, 1, (ll)-1e14};
    pq.push(e);
    edges.insert(e);

    ll ans = 0;
    for (int i = 0; i < (n + 1) / 2;) {
        Edge curr = pq.top();
        pq.pop();
        if (!visited[curr.l] && !visited[curr.r]) {
            i++;
            ans += curr.cost;
            visited[curr.l] = visited[curr.r] = true;

            auto it = edges.find(curr);
            Edge l = *prev(it), r = *next(it);
            Edge newedge = merge(l, curr, r);
            edges.erase(l); edges.erase(curr); edges.erase(r);
            edges.insert(newedge);
            pq.push(newedge);

            cout << ans << '\n';
        }
    }
    return 0;
}