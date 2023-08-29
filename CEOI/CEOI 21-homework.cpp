#include <bits/stdc++.h>
using namespace std;
 
const int N = 2000001;
 
vector<int> graph[N];
int p[N], n = 0, type[N], sz[N], mn[N], mx[N];
 
void dfs(int node = 1) {
	if (!graph[node].size()) return;
	int u = graph[node][0], v = graph[node][1];
	dfs(u);
	dfs(v);
	sz[node] += sz[u] + sz[v];
	if (type[node] == 1) {  // min
		mn[node] = min(mn[u], mn[v]);
		mx[node] = mx[u] + mx[v] - 1;
	} else if (type[node] == 2) {  // max
		mn[node] = mn[u] + mn[v];
		mx[node] = max(sz[u] + mx[v], sz[v] + mx[u]);
	}
}

int main() {
	string s;
	cin >> s;
	int curr = 0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'm') {
			p[++n] = curr;
			graph[curr].push_back(n);
			curr = n;
			if (s[i + 2] == 'n') type[curr] = 1;  // min
			else type[curr] = 2;  // max
			i += 3;
		} else if (s[i] == '?') {
			p[++n] = curr;
			graph[curr].push_back(n);
			curr = n;
			mn[curr] = mx[curr] = sz[curr] = 1;
		} else curr = p[curr];
	}
	dfs();
	cout << mx[1] - mn[1] + 1;
	return 0;
}
