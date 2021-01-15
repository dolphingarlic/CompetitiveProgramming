#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> graph[200001];
int subtree[200001];

void get_subtree_sizes(int node = 1, int parent = 0) {
    subtree[node] = 1;
    for (int i : graph[node]) if (i != parent) {
        get_subtree_sizes(i, node);
        subtree[node] += subtree[i];
    }
}

int get_centroid(int desired, int node = 1, int parent = 0) {
    for (int i : graph[node]) if (i != parent && subtree[i] > desired)
        return get_centroid(desired, i, node);
    return node;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    get_subtree_sizes();
    cout << get_centroid(n / 2);
    return 0;
}