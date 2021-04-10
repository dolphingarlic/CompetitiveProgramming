#include <bits/stdc++.h>
using namespace std;

int l[100];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < 2 * n; i++) cin >> l[i];
    sort(l, l + 2 * n);
    int ans = 0;
    for (int i = 0; i < 2 * n; i += 2) ans += l[i];
    cout << ans;
    return 0;
}
