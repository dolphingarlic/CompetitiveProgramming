#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
pair<int, int> a[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i].second >> a[i].first;
    sort(a, a + n);
    multiset<int> ends;
    for (int i = 0; i < k; i++) ends.insert(1);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (ends.upper_bound(a[i].second) != ends.begin()) {
            ans++;
            ends.erase(prev(ends.upper_bound(a[i].second)));
            ends.insert(a[i].first);
        }
    }
    cout << ans;
    return 0;
}