#include "cross.h"
#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll SelectCross(int K, vector<int> I, vector<int> O) {
	int N = I.size();
	vector<pair<ll, ll>> crosses;
	FOR(i, 0, N) crosses.push_back({I[i], O[i]});
	sort(crosses.begin(), crosses.end(), greater<pair<ll, ll>>());

	priority_queue<ll> pq;
	ll ans = 0;
	FOR(i, 0, N) {
		pq.push(-crosses[i].second);
		if (i >= K) pq.pop();
		if (i >= K - 1) ans = max(ans, -pq.top() * crosses[i].first * 2 - crosses[i].first * crosses[i].first);
	}

	return ans;
}
