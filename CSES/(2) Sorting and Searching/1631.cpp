#include <bits/stdc++.h>
using namespace std;
 
long long a[200000];
 
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%lld", a + i);
	sort(a, a + n);
	printf("%lld", max(2 * a[n - 1], accumulate(a, a + n, 0ll)));
	return 0;
}