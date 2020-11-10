#include <bits/stdc++.h>
using namespace std;

vector<int> graph[5001];

void find_dep(int node, int parent, pair<int, vector<int>> &root, int depth = 0) {
    if (depth == root.first) {
        root.first++;
        root.second.push_back(1);
    } else root.second[depth]++;
    for (int i : graph[node]) if (i != parent) find_dep(i, node, root, depth + 1);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    if (n < 4) {
        printf("0\n");
        return 0;
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        int m = graph[i].size();
        vector<pair<int, vector<int>>> dep(m);
        vector<vector<int>> aft(m);
        for (int j = 0; j < m; j++) find_dep(graph[i][j], i, dep[j]);
        vector<int> tot(max_element(dep.begin(), dep.end())->first, 0);

        for (int j = m - 1; ~j; j--) {
            aft[j].resize(dep[j].first);
            for (int k = 0; k < dep[j].first; k++) {
                aft[j][k] = tot[k];
                tot[k] += dep[j].second[k];
            }
        }

        for (int j = 0; j < m; j++) {
            for (int k = 0; k < dep[j].first; k++) {
                ans += (tot[k] - dep[j].second[k] - aft[j][k]) * dep[j].second[k] * aft[j][k];
            }
        }
    }
    
    printf("%lld\n", ans);
    return 0;
}