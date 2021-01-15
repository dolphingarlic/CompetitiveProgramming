#include <iostream>
#include <set>
using namespace std;
 
multiset<int> ms;
 
int main() {
	int n, m;
	cin >> n >> m;
	while (n--) {
		int k;
		cin >> k;
		ms.insert(k);
	}
	while (m--) {
		int k;
		cin >> k;
		if (ms.upper_bound(k) == ms.begin()) cout << "-1\n";
		else {
			cout << *prev(ms.upper_bound(k)) << '\n';
			ms.erase(prev(ms.upper_bound(k)));
		}
	}
	return 0;
}