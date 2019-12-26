#include <bits/stdc++.h>
using namespace std;

double a[100000], b[100000];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
	sort(a, a + n, greater<double>());
	sort(b, b + n, greater<double>());
	
	double ans = 0, l = 0, r = 0;
	int lptr = 0, rptr = 0;
	for (int i = 1; i <= 2 * n; i++) {
		if (lptr < n && (rptr == n || l < r)) l += a[lptr++];
		else r += b[rptr++];
		ans = max(ans, min(l, r) - i);
	}
	
	cout << fixed << setprecision(4) << ans;
	return 0;
}
