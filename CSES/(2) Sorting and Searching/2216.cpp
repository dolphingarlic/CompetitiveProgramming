#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int pos[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        pos[a] = i;
    }
    int ans = 1;
    for (int i = 1; i < n; i++) ans += (pos[i + 1] < pos[i]);
    cout << ans;
    return 0;
}