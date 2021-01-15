#include <iostream>
#include <algorithm>
using namespace std;
 
pair<int, int> events[400001];
 
int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		events[i * 2] = {a, 1};
		events[i * 2 + 1] = {b, -1};
	}
	sort(events, events + 2 * n);
	
	int ans = 0, cnt = 0;
	for (int i = 0; i < 2 * n; i++) {
		cnt += events[i].second;
		ans = max(ans, cnt);
	}
	
	cout << ans;
	return 0;
}