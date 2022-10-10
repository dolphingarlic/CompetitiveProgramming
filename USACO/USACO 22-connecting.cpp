#include <iostream>
#include <vector>
using namespace std;

vector<int> graph[100001];


void dfs(int node) {

}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, );
    return 0;
}
