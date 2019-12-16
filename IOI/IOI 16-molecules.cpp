#include <bits/stdc++.h>
#include "molecules.h"
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;
 
pair<long long, int> a[200001];
long long pref[200001]{0};
 
vector<int> find_subset(int l, int u, vector<int> w) {
	int n = w.size();
	FOR(i, 0, n) {
		a[i].first = (long long)w[i];
		a[i].second = i;
	}
	sort(a, a + n);
	FOR(i, 0, n) pref[i + 1] = pref[i] + a[i].first;
 
	vector<int> res;
	int x = 1, y = n;
	while (x <= y) {
		int mid = (x + y) / 2;
		bool too_big = false;
		FOR(i, 0, n - mid + 1) {
			long long sum = pref[i + mid] - pref[i];
			if (sum >= l && sum <= u) {
				FOR(j, i, i + mid) res.push_back(a[j].second);
				return res;
			} else if (sum > u) {
				too_big = true;
				break;
			}
		}
		if (too_big) y = mid - 1;
		else x = mid + 1;
	}
 
	return res;
}