#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[200001];
map<int, int> cnt;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    for (int i = 0, lptr = 0; i < n; i++) {
        cin >> a[i];
        cnt[a[i]]++;
        while (cnt.size() > k) {
            cnt[a[lptr]]--;
            if (!cnt[a[lptr]]) cnt.erase(a[lptr]);
            lptr++;
        }
        ans += i - lptr + 1;
    }
    cout << ans;
    return 0;
}