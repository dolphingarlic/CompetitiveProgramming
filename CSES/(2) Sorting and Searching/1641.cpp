#include <bits/stdc++.h>
using namespace std;
 
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
int a[5001];
gp_hash_table<int, pair<short, short>> mp({}, {}, {}, {}, {1<<25});
 
int main() {
	short n;
	int x;
	scanf("%d %d", &n, &x);
	for (short i = 1; i <= n; i++) {
		scanf("%d", a + i);
		if (mp.find(x - a[i]) != mp.end()) {
			printf("%d %d %d", mp[x - a[i]].first, mp[x - a[i]].second, i);
			return 0;
		}
		for (short j = 1; j < i; j++) mp[a[i] + a[j]] = {j, i};
	}
	printf("IMPOSSIBLE");
	return 0;
}