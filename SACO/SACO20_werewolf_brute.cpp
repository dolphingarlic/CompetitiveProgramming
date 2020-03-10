#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int N, M, Q, T;
ll V[200001];

vector<int> graph[200001];
set<pair<ll, int>> visited;

void dfs(int node, int R) {
    visited.insert({V[node], node});
    for (int i : graph[node]) {
        if (i <= R && visited.find({V[i], i}) == visited.end())
            dfs(i, R);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M >> Q >> T;
    FOR(i, 0, N) cin >> V[i];
    FOR(i, 0, M) {
        int X, Y;
        cin >> X >> Y;
        graph[X].push_back(Y);
        graph[Y].push_back(X);
    }
    while (Q--) {
        int S, R;
        cin >> S >> R;
        dfs(S, R);
        int rem = T, ans = 0;
        while (visited.size() && rem >= (*visited.begin()).first) {
            ans++;
            rem -= (*visited.begin()).first;
            visited.erase(visited.begin());
        }
        cout << ans << '\n';
        visited.clear();
    }
    return 0;
}