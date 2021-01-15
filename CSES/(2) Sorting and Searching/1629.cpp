#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
pair<int, int> a[200001];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i].second >> a[i].first;
    sort(a, a + n);
    int curr_end = -1, ans = 0;
    FOR(i, 0, n) {
        if (curr_end <= a[i].second) {
            ans++;
            curr_end = a[i].first;
        }
    }
    cout << ans;
    return 0;
}