#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
typedef long long ll;
using namespace std;

pair<ll, ll> rec[1001];
int intended[1001], res[1001];
vector<int> graph[1001];
int par[1001], din[1001];
bool visited[1001];

bool interfere(pair<ll, ll> a, pair<ll, ll> b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) <= 100;
}

void dfs(int node = 0, int parent = -1) {
    if (~parent) din[parent]++;
    par[node] = parent;
    for (int i : graph[node]) if (i != parent) dfs(i, node);
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> rec[i].x >> rec[i].y;
    FOR(i, 0, n) cin >> intended[i];
    FOR(i, 0, n) FOR(j, i + 1, n) if (interfere(rec[i], rec[j])) {
        graph[i].push_back(j);
        graph[j].push_back(i);
    }

    set<int> s;
    FOR(i, 0, n) if (intended[i]) s.insert(i);
    while (s.size()) {
        int node = *s.begin();
        visited[node] = true;
        for (int i : graph[node]) {
            if (!visited[i]) {
                visited[i] = true;
                if ()
            }
        }
    }

    dfs();

    vector<int> q;
    FOR(i, 0, n) if (!din[i]) q.push_back(i);
    while (q.size()) {
        int curr = q.back();
        q.pop_back();
        // Do stuff with curr
        din[par[curr]]--;
        if (!din[par[curr]]) q.push_back(par[curr]);
    }
    return 0;
}