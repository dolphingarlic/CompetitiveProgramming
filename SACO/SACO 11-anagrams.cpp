#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int k[100001];
int i_cnt[20000], a_cnt[20000], match = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

	int n, m;
	cin >> n >> m;
	FOR(i, 0, n) {
		int x;
		cin >> x;
		i_cnt[x]++;
	}
	FOR(i, 0, n) {
		cin >> k[i];
		a_cnt[k[i]]++;
	}
	FOR(i, 0, 20000) if (i_cnt[i] == a_cnt[i]) match++;
	int ans = (match == 20000);
	FOR(i, n, m) {
		cin >> k[i];
		a_cnt[k[i]]++;
		if (a_cnt[k[i]] == i_cnt[k[i]]) match++;
		else if (a_cnt[k[i]] == i_cnt[k[i]] + 1) match--;
		
		a_cnt[k[i - n]]--;
		if (a_cnt[k[i - n]] == i_cnt[k[i - n]]) match++;
		else if (a_cnt[k[i - n]] == i_cnt[k[i - n]] - 1) match--;
		
		if (match == 20000) ans++;
	}
	cout << ans;
	return 0;
}