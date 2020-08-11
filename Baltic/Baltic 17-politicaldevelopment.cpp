/*
Baltic 2017 Political Development
- While there exists some politician with degree < K, check whether
  we can form a good committee using the politicians he disagrees with
  that is larger than the largest committee we can make so far
    - Then erase him from existence afterwards
- No idea why this works/why this is fast enough, but it gets AC
- Complexity: O(NK^2 log K * 2^K)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<int> graph[50000];
bool tried[50000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    queue<int> q;
    for (int i = 0; i < n; i++) {
        int s;
        cin >> s;
        if (s < k) {
            tried[i] = true;
            q.push(i);
        }
        while (s--) {
            int b;
            cin >> b;
            graph[i].insert(b);
        }
    }

    int ans = 0;
    while (q.size()) {
        int curr = q.front();
        q.pop();

        for (int i = 0; i < (1 << graph[curr].size()); i++) {
            if (__builtin_popcount(i) <= ans) continue;
            vector<int> adj;
            int tmp = i;
            for (int j : graph[curr]) {
                if (tmp & 1) adj.push_back(j);
                tmp >>= 1;
            }
            bool good = true;
            for (int j = 0; j < adj.size(); j++) {
                for (int l = j + 1; l < adj.size(); l++) {
                    good &= graph[adj[j]].find(adj[l]) != graph[adj[j]].end();
                }
            }
            if (good) ans = __builtin_popcount(i);
        }

        for (int i : graph[curr]) {
            graph[i].erase(curr);
            if (!tried[i] && graph[i].size() < k) {
                tried[i] = true;
                q.push(i);
            }
        }
        graph[curr].clear();
    }

    cout << ans + 1;
    return 0;
}