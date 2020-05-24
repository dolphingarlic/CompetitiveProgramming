/*
POI 2012 Salaries
- Firstly, what happens if we only know the salary of 1 person - the CEO?
    - We can determine the salaries of person i's children only if i only
      has 1 child
    - Additionally, the number of unknown salaries must be equal to the
      number of unknown nodes
        - If the number of unknown salaries is greater, none of those
          salaries can be determined
- We know the CEO will always have salary N
- For each known node, erase the edge going to its parent
- We end up with a forest where each tree has only the root known
- If we sort the trees by their root, we can solve this problem greedily
- Consider a tree with root A[i] and B[i] unknown nodes
- Let K[i] be the set of unknown salaries less than A[i]
- If len(K[i]) == B[i], we just DFS and greedily assign the largest value
  of K[i] until we reach a node with more than 1 child
- Otherwise, mark all values in K[i] as invalid
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<int> graph[1000001], k, forest;
int s[1000001], lab[1000001];
bool unknown[1000001];

int dfs(int node) {
    int ans = 1;
    for (int i : graph[node]) ans += dfs(i);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        int p;
        cin >> p >> s[i];
        if (p == i) s[i] = n;
        if (!s[i]) graph[p].push_back(i);
        else forest.push_back(i);
        lab[s[i]] = i;
    }
    sort(forest.begin(), forest.end(), [](int A, int B) { return s[A] < s[B]; });
    FOR(i, 1, n + 1) if (!lab[i]) k.push_back(i);

    int l = 0, r = 0, ptr = 0;
    for (int i : forest) {
        int sz = dfs(i) - 1;
        if (!sz) continue;

        l = r;
        while (r < k.size() && k[r] < s[i] && r - l < sz) r++;

        if (r == k.size() || k[r] > s[i])
            for (int j = r - 1, node = i; j >= l && graph[node].size() == 1; j--, node = graph[node][0])
                s[graph[node][0]] = k[j];
        while (ptr < k.size() && k[ptr] < s[i]) unknown[k[ptr++]] = !(r == k.size() || k[r] > s[i]);
    }

    FOR(i, 1, n + 1) cout << (unknown[s[i]] ? 0 : s[i]) << '\n';
    return 0;
}