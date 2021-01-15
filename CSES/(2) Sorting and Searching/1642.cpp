#include <bits/stdc++.h>
using namespace std;
 
int a[5001];
map<int, vector<pair<short, short>>> mp;
 
int main() {
	short n;
	int x;
	scanf("%d %d", &n, &x);
	for (short i = 1; i <= n; i++) scanf("%d", a + i);
	for (short i = 1; i <= n; i++) for (short j = 1; j < i; j++)
		mp[a[i] + a[j]].push_back({j, i});
	for (short i = 1; i <= n; i++) for (short j = 1; j < i; j++) {
		for (pair<short, short> k : mp[x - a[i] - a[j]]) {
			if (i != k.first && i != k.second && j != k.first && j != k.second) {
				printf("%d %d %d %d", i, j, k.first, k.second);
				return 0;
			}
		}
	}
	printf("IMPOSSIBLE");
	return 0;
}