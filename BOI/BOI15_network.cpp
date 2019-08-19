#include <bits/stdc++.h>
using namespace std;
 
vector<int> graph[500001], leaves;
 
void dfs(int node = 1, int parent = 0) {
	if (graph[node].size() == 1) leaves.push_back(node);
	for (int i : graph[node]) {
		if (i == parent) continue;
		dfs(i, node);
	}
}
 
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	dfs();

	cout << (leaves.size() + 1) / 2 << '\n';
	for (int i = 0; i < (leaves.size() + 1) / 2; i++) cout << leaves[i] << ' ' << leaves[i + leaves.size() / 2] << '\n';
	return 0;
}