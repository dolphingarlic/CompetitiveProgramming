#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int N;

vector<int> graph[50001];
set<int> *dp[50001];

void dfs(int node, int parent = -1) {
    int mx_size = 0, mx_child = -1;
    for (int i : graph[node]) {
        if (i != parent) {
            dfs(i, node);
            if (dp[i]->size() > mx_size) mx_size = dp[i]->size(), mx_child = i;
        }
    }

    if (mx_child == -1)
        dp[node] = new set<int>{0};
    else {
        set<int> *f = dp[mx_child];
        int a = -1;
        for (int i : graph[node]) {
            if (i != parent && i != mx_child) {
                for (int j : *dp[i]) {
                    if (f->find(j) != f->end())
                        a = max(a, j);
                    else
                        f->insert(j);
                }
            }
        }
        int b = a + 1;
        set<int> *ret = new set<int>(f->lower_bound(b), f->end());
        while (ret->size() && *ret->begin() == b) {
            b++;
            ret->erase(ret->begin());
        }
        ret->insert(b);
        dp[node] = ret;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    FOR(i, 1, N) {
        ll a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    dfs(1);
    cout << *prev(dp[1]->end());
    return 0;
}
