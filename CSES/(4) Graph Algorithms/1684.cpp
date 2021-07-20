#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> graph[200001], rev[200001];
bool visited[200001];
stack<int> stck;
int scc = 0, cmp[200001];
char ans[100001];

void dfs1(int node) {
    visited[node] = true;
    for (int i : graph[node]) if (!visited[i]) dfs1(i);
    stck.push(node);
}

void dfs2(int node) {
    cmp[node] = scc;
    for (int i : rev[node]) if (!cmp[i]) dfs2(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (n--) {
        char c1, c2;
        int t1, t2;
        cin >> c1 >> t1 >> c2 >> t2;
        graph[t1 * 2 - (c1 == '+')].push_back(t2 * 2 - (c2 == '-'));
        graph[t2 * 2 - (c2 == '+')].push_back(t1 * 2 - (c1 == '-'));
    }
    for (int i = 1; i <= 2 * m; i++) if (!visited[i])
        dfs1(i);
    for (int i = 1; i <= 2 * m; i++) for (int j : graph[i])
        rev[j].push_back(i);
    while (stck.size()) {
        int curr = stck.top();
        stck.pop();
        if (!cmp[curr]) {
            scc++;
            dfs2(curr);
        }
    }
    for (int i = 1; i <= m; i++) {
        if (cmp[2 * i - 1] == cmp[2 * i]) return cout << "IMPOSSIBLE", 0;
        ans[i] = (cmp[2 * i - 1] < cmp[2 * i] ? '+' : '-');
    }
    for (int i = 1; i <= m; i++) cout << ans[i] << ' ';
    return 0;
}