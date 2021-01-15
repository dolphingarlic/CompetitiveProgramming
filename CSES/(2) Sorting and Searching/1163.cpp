#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int x, n;
	scanf("%d %d", &x, &n);
	multiset<int> gaps;
	gaps.insert(x);
	set<int> lights;
	lights.insert(0), lights.insert(x);
	while (n--) {
		int p;
		scanf("%d", &p);
		auto ub = lights.upper_bound(p);
		int g = *ub - *prev(ub);
		gaps.erase(gaps.find(g));
		gaps.insert(*ub - p), gaps.insert(p - *prev(ub));
		lights.insert(p);
		printf("%d ", *gaps.rbegin());
	}
}