#include <bits/stdc++.h>
#define FOR(i, x, y) for (long long i = x; i < y; i++)
using namespace std;

long long pref[1000001], dp[1000001];
long long n, a, b, c;

bool case1(long long x, long long y, long long i) {
  return (dp[y] - dp[x] + a * (pref[y] * pref[y] - pref[x] * pref[x]) > (2 * a * pref[i] + b) * (pref[y] - pref[x]));
}

bool case2(long long x, long long y, long long i) {
	return ((dp[y] - dp[x] + a * (pref[y] * pref[y] - pref[x] * pref[x])) * (pref[i] - pref[y]) < (dp[i] - dp[y] + a * (pref[i] * pref[i] - pref[y] * pref[y])) * (pref[y] - pref[x]));
}

int main() {
  cin >> n >> a >> b >> c;
  FOR(i, 0, n) {
	long long x;
	cin >> x;
	pref[i + 1] = pref[i] + x;
  }

  deque<long long> q;
  q.push_back(0);
  dp[0] = 0;
  FOR(i, 1, n + 1) {
	while (q.size() > 1 && case1(q[0], q[1], i)) q.pop_front();

	long long x = q[0];
	long long y = pref[i] - pref[x];
	dp[i] = dp[x] + a * y * y + b * y + c;

	while (q.size() > 1 && case2(q[q.size() - 2], q.back(), i)) q.pop_back();

	q.push_back(i);
  }

  cout << dp[n] << '\n';
}