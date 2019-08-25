#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<int> graph[50001];

pair<int, int> dfs(int node, int parent) {
    int ans = 0, bestnode = node;
    for (int i : graph[node]) {
        if (i != parent) {
            pair<int, int> k = dfs(i, node);
            if (k.first > ans) ans = k.first, bestnode = k.second;
        }
    }
    return {ans + 1, bestnode};
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    cout << dfs(dfs(1, 0).second, 0).first;
    
    return 0;
}