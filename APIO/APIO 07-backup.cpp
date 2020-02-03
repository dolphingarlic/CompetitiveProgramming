/*
APIO 2007 Backup
- Firstly, notice that the optimal solution's connections are only
  between consecutive buildings
    - Let the distances between buildings be a[i]
- Next, notice that if we have some a[i] < a[i - 1] and a[i] < a[i + 1]
  then if we don't take a[i] in our solution, we must take both
  a[i - 1] and a[i + 1]
    - Assume for a contradiction that we take at most one of them
    - Since a[i] < a[i - 1] and a[i] < a[i + 1], we can just instead take
      a[i] and not the one we originally took and get a shorter solution
- From this, we construct the following greedy solution using a priority queue
    - First, have "edges" of the form {i, i + 1, a[i]}
    - Put these edges in a priority queue
    - Consider the cheapest edge E
        - If neither i or i + 1 are used, take edge E
        - If we take edge E, merge E with its 2 neighbouring edges D and F
          to get a new edge with cost = D.cost + F.cost - E.cost
            - If we take this edge, we effectively undo us taking E
- Complexity: O((N + K) log N)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Edge {
    int l, r;
    ll cost;
};
bool operator<(Edge A, Edge B) { return A.l < B.l; }
bool operator>(Edge A, Edge B) { return A.cost > B.cost; }

Edge merge(Edge A, Edge B, Edge C) { return {A.l, C.r, A.cost + C.cost - B.cost}; }

bool visited[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;

    ll a = -1e14, b;
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    set<Edge> edges;
    for (int i = 0; i < n; i++) {
        cin >> b;
        Edge e = {i, i + 1, b - a};
        pq.push(e);
        edges.insert(e);
        a = b;
    }
    Edge e = {n, n + 1, (ll)1e14};
    pq.push(e);
    edges.insert(e);

    ll ans = 0;
    while (k) {
        Edge curr = pq.top();
        pq.pop();
        if (!visited[curr.l] && !visited[curr.r]) {
            k--;
            ans += curr.cost;
            visited[curr.l] = visited[curr.r] = true;

            auto it = edges.find(curr);
            Edge l = *prev(it), r = *next(it);
            Edge newedge = merge(l, curr, r);
            edges.erase(l); edges.erase(curr); edges.erase(r);
            edges.insert(newedge);
            pq.push(newedge);
        }
    }
    cout << ans << '\n';
    return 0;
}