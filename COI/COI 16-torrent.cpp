/*
COI 2016 Torrent
- Let's consider the case where there's only 1 computer with a file
    - Let dp[i] = Min. time to process subtree i
    - Let L be a sorted list of i's children's dp values
    - dp[i] = max(L[j] + j + 1)
- In the case where there are two computers with a file, consider the
  "chain" of the path between them. Let's say they're numbered 1 to M
- The optimal procedure will be like
    (Computer 1 sends to some children) -> (Computer 1 sends to computer 2) -> ..., and
    (Computer M sends to some children) -> (Computer M sends to computer M - 1) -> ...
- To determine which children each computer sends data to before sending
  to the next computer on the chain, we can use binary search and suffix maximums
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, a, b, dp[300001];
vector<int> graph[300001], chain, chain_cdp[300001];
bool on_chain[300001], good[300001];

bool find_chain(int node = a, int parent = 0) {
    if (node == b) {
        chain.push_back(node);
        on_chain[node] = true;
        return true;
    }
    for (int i : graph[node]) if (i != parent && find_chain(i, node)) {
        chain.push_back(node);
        on_chain[node] = true;
        return true;
    }
    return false;
}

void calc_dp(int node, int parent = 0) {
    vector<int> cdp;
    for (int i : graph[node]) if (i != parent && !on_chain[i]) {
        calc_dp(i, node);
        cdp.push_back(dp[i]);
    }
    sort(cdp.begin(), cdp.end(), greater<int>());
    for (int i = 0; i < cdp.size(); i++) {
        cdp[i] += i + 1;
        dp[node] = max(dp[node], cdp[i]);
    }
    if (on_chain[node]) {
        for (int i = cdp.size() - 2; i >= 0; i--) cdp[i] = max(cdp[i], cdp[i + 1]);
        chain_cdp[node] = cdp;
    }
}

bool check(int pot) {
    for (int i : chain) good[i] = false;

    for (int _ : {0, 1}) {
        int curr_time = 0;
        for (int i : chain) {
            good[i] |= (curr_time + dp[i] <= pot);
            int delta;
            for (delta = 0; delta < chain_cdp[i].size(); delta++) {
                if (curr_time + chain_cdp[i][delta] < pot) break;
            }
            curr_time += delta + 1;
        }
        reverse(chain.begin(), chain.end());
    }

    bool res = true;
    for (int i : chain) res &= good[i];
    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> a >> b;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    find_chain();
    for (int i : chain) calc_dp(i);

    int l = 0, r = n;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}
