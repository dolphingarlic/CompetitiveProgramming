#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int x[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    map<int, int> pos;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        pos[x[i]] = i;
    }
    sort(x, x + n);
    int ans = 0;
    for (int i = 0; i < n; i += 2) if (abs(i - pos[x[i]]) & 1) ans++;
    cout << ans;
    return 0;
}
