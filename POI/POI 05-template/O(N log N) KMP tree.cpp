/*
POI 2005 Template
- Same as amortized O(N), but we make a "KMP tree"
- The subree of node i would be the set of positions matching S[0 : i]
- We can thus use a std::multiset to keep track of gaps between matches
*/

#include <bits/stdc++.h>
using namespace std;

string s;
int p[500000];
vector<int> graph[500000];
bool visited[500000];
set<int> matches;
multiset<int> gaps;

void dfs(int node) {
    visited[node] = true;
    set<int>::iterator ub = matches.upper_bound(node);
    int l = *prev(ub), r = *ub;
    gaps.erase(gaps.find(r - l));
    gaps.insert(node - l), gaps.insert(r - node);
    matches.insert(node);
    for (int i : graph[node]) if (!visited[i]) dfs(i);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> s;
    int n = s.size();
    for (int i = 1; i < n; i++) {
        p[i] = p[i - 1];
        while (p[i] && s[i] != s[p[i]]) p[i] = p[p[i] - 1];
        if (s[i] == s[p[i]]) p[i]++;
        if (p[i]) graph[p[i] - 1].push_back(i);
    }
    int ans = n;
    matches.insert(-1), matches.insert(n);
    gaps.insert(n + 1);
    for (int i = n; i; i = p[i - 1]) {
        dfs(i - 1);
        if (*gaps.rbegin() <= i) ans = i;
    }
    cout << ans;
    return 0;
}
