#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int x[200001];
map<int, int> cnt;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, ans = 0, lptr = 0;
    cin >> n;
    FOR(i, 0, n) {
        cin >> x[i];
        cnt[x[i]]++;
        while (cnt[x[i]] > 1) cnt[x[lptr++]]--;
        ans = max(ans, i - lptr + 1);
    }
    cout << ans;
    return 0;
}
