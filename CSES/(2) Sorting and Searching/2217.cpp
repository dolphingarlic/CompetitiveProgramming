#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int pos[200002], at[200002];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> at[i];
        pos[at[i]] = i;
    }
    pos[0] = 0, pos[n + 1] = n + 1;

    int ans = 1;
    for (int i = 1; i < n; i++) ans += (pos[i + 1] < pos[i]);
    while (m--) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        ans -= (pos[at[a] + 1] < pos[at[a]]) + (pos[at[a]] < pos[at[a] - 1]);
        ans -= (pos[at[b] + 1] < pos[at[b]]) + (pos[at[b]] < pos[at[b] - 1]);
        swap(pos[at[a]], pos[at[b]]);
        swap(at[a], at[b]);
        ans += (pos[at[a] + 1] < pos[at[a]]) + (pos[at[a]] < pos[at[a] - 1]);
        ans += (pos[at[b] + 1] < pos[at[b]]) + (pos[at[b]] < pos[at[b] - 1]);
        if (at[a] == at[b] + 1) ans--;
        if (at[a] == at[b] - 1) ans++;
        cout << ans << '\n';
    }
    return 0;
}