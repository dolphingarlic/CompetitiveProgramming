/*
Biconnected Components
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[100001], stck;
vector<vector<int>> bccs;
int low[100001], tin[100001], timer = 1;

void dfs(int node = 1, int parent = 0) {
    low[node] = tin[node] = timer++;
    stck.push_back(node);

    for (int i : graph[node]) if (i != parent) {
        if (tin[i]) low[node] = min(low[node], tin[i]);
        else {
            dfs(i, node);
            low[node] = min(low[node], low[i]);

            if (low[i] >= tin[node]) {
                bccs.push_back(vector<int>());
                int lst = -1;
                do {
                    bccs.back().push_back(stck.back());
                    lst = stck.back();
                    stck.pop_back();
                } while (!stck.empty() && lst != i);
                bccs.back().push_back(node);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("biconex.in");
    ofstream cout("biconex.out");

    int n, m;
    cin >> n >> m;
    FOR(i, 0, m) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs();

    cout << bccs.size() << '\n';
    for (vector<int> i :  bccs) {
        for (int j : i) cout << j << ' ';
        cout << '\n';
    }
    return 0;
}