#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<int> graph[100001];
array<int, 3> ops[100001];
int visited[100001], colour[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
        cin >> ops[i][0] >> ops[i][1] >> ops[i][2];

    while (q--) if (visited[ops[q][0]] < ops[q][1] + 1) {
        if (!visited[ops[q][0]]) colour[ops[q][0]] = ops[q][2];
        visited[ops[q][0]] = ops[q][1] + 1;
        queue<pair<int, int>> qu;
        qu.push({ops[q][0], ops[q][1] + 1});
        while (qu.size()) {
            int curr, dist;
            tie(curr, dist) = qu.front();
            qu.pop();
            for (int i : graph[curr]) if (visited[i] < dist - 1) {
                if (!visited[i]) colour[i] = ops[q][2];
                visited[i] = dist - 1;
                qu.push({i, dist - 1});
            }
        }
    }
    for (int i = 1; i <= n; i++) cout << colour[i] << '\n';
    return 0;
}
