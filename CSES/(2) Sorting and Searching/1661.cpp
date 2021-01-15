#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
map<ll, ll> cnt;
 
int main() {
    int n;
    ll x;
    scanf("%d %lld", &n, &x);
    ll pref = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        cnt[pref]++;
        ll a;
        scanf("%lld", &a);
        pref += a;
        ans += cnt[pref - x];
    }
    printf("%lld", ans);
    return 0;
}