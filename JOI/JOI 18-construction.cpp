/*
JOI 2018 Construction of Highway
- First, construct the HLD on the full tree
- In each heavy path, we naively store the values on it, but "compressed"
    - Group equal adjacent values together
- We can then get a list of the values on the path from 1 to A[i] (let's say length M)
    - M is O(log^2 N) on average I think
- Using a BIT, we can count the number of inversions in this list in O(M log M) time
- This is amortized O(N log^2 N) for reasons I don't fully understand
    - The reasoning is that if we process many different values in some individual query,
      then those different values all become the same in subsequent queries
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int c[100001], u[100001], v[100001], par[100001];
vector<int> graph[100001];
int heavy[100001], head[100001], depth[100001];
deque<pair<int, int>> hld_vals[100001];

int dfs(int node = 1) {
    int sz = 1, mx = 0;
    for (int i : graph[node]) {
        int csz = dfs(i);
        sz += csz;
        if (csz > mx) mx = csz, heavy[node] = i;
    }
    return sz;
}

void decompose(int node = 1, int h = 1, int d = 1) {
    head[node] = h; depth[node] = d;
    if (heavy[node]) decompose(heavy[node], h, d + 1);
    for (int i : graph[node]) if (i != heavy[node]) decompose(i, i, 1);
}

ll count_inversions(deque<pair<int, int>> &path) {
    map<int, int> comp;
    for (pair<int, int> i : path) comp[i.first];
    int n = 0;
    for (auto &i : comp) i.second = ++n;

    ll ans = 0;
    vector<ll> bit(n + 1);
    for (pair<int, int> i : path) {
        for (int j = comp[i.first] - 1; j; j -= j & -j) ans += bit[j] * i.second;
        for (int j = comp[i.first]; j <= n; j += j & -j) bit[j] += i.second;
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> c[i];
    for (int i = 1; i < n; i++) {
        cin >> u[i] >> v[i];
        graph[u[i]].push_back(v[i]);
        par[v[i]] = u[i];
    }
    dfs(); decompose();

    hld_vals[1].push_back({c[1], 1});
    for (int i = 1; i < n; i++) {
        deque<pair<int, int>> path;
        int curr = v[i];
        while (curr) {
            deque<pair<int, int>> ins;
            int rem = depth[curr] - (curr == v[i]), h = head[curr];
            while (rem) {
                if (hld_vals[h][0].second <= rem) {
                    rem -= hld_vals[h][0].second;
                    ins.push_front(hld_vals[h][0]);
                    hld_vals[h].pop_front();
                } else {
                    ins.push_front({hld_vals[h][0].first, rem});
                    pair<int, int> upd = {hld_vals[h][0].first, hld_vals[h][0].second - rem};
                    hld_vals[h].pop_front();
                    hld_vals[h].push_front(upd);
                    rem = 0;
                }
            }
            hld_vals[h].push_front({c[v[i]], depth[curr]});
            path.insert(path.end(), ins.begin(), ins.end());
            curr = par[h];
        }
        cout << count_inversions(path) << '\n';
    }
    return 0;
}
