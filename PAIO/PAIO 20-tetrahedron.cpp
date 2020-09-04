#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[1500], divi[1500];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
        divi[i] += (a[j] % a[i] == 0);
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
        if (a[j] % a[i] == 0) ans += divi[j];
    }
    cout << ans;
    return 0;
}