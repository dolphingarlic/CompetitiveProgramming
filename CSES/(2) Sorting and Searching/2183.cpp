#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[200001], pref = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        if (pref + 1 < a[i]) return cout << pref + 1, 0;
        pref += a[i];
    }
    cout << pref + 1;
    return 0;
}