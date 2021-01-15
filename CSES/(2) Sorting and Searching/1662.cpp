#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
map<ll, ll> cnt;
 
int main() {
    int n;
    scanf("%d", &n);
    ll pref = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        cnt[pref]++;
        ll a;
        scanf("%lld", &a);
        pref = ((pref + a) % n + n) % n;
        ans += cnt[pref];
    }
    printf("%lld", ans);
    return 0;
}