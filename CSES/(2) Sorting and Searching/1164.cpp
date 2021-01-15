#include <bits/stdc++.h>
using namespace std;
 
int alloc[200001];
set<int> available;
vector<pair<int, int>> events;
 
int main() {
	int n, mn = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		events.push_back({a, -i});
		events.push_back({b, i});
	}
	sort(events.begin(), events.end());
	for (pair<int, int> i : events) {
		if (i.second < 0) {
			if (available.size()) alloc[-i.second] = *available.begin();
			else alloc[-i.second] = ++mn;
			available.erase(alloc[-i.second]);
		} else available.insert(alloc[i.second]);
	}
	printf("%d\n", mn);
	for (int i = 1; i <= n; i++) printf("%d ", alloc[i]);
	return 0;
}