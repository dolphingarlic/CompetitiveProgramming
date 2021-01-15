#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
pair<int, int> a[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    cin >> n >> x;
    FOR(i, 0, n) {
        cin >> a[i].first;
        a[i].second = i + 1;
    }
    sort(a, a + n);
    FOR(i, 0, n) {
        pair<int, int> lb = *lower_bound(a, a + n, make_pair(x - a[i].first, -1));
        if (lb != a[i] && a[i].first + lb.first == x) {
            return cout << a[i].second << ' ' << lb.second, 0;
        }
    }
    cout << "IMPOSSIBLE";
    return 0;
}