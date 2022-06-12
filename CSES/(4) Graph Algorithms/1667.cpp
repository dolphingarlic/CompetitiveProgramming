#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int visited[100001], backtrack[100001];
vector<int> graph[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    queue<int> q;
    q.push(n);
    visited[n] = 1;
    while (q.size()) {
        int curr = q.front();
        q.pop();
        for (int i : graph[curr]) if (!visited[i]) {
            visited[i] = visited[curr] + 1;
            backtrack[i] = curr;
            q.push(i);
        }
    }
    if (visited[1]) {
        cout << visited[1] << '\n';
        for (int i = 0, curr = 1; i < visited[1]; i++, curr = backtrack[curr])
            cout << curr << ' ';
    } else cout << "IMPOSSIBLE";
}
