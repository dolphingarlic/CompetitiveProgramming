#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int _ = 1; _ <= t; _++) {
        cout << "Case #" << _ << ": ";
        int n, c;
        cin >> n >> c;
        if (c < n - 1 || n * (n + 1) / 2 - 1 < c) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        c -= n - 1;
        vector<int> to_reverse(n);
        for (int i = 0; i < n - 1; i++) {
            to_reverse[i] = min(c, n - i - 1);
            c -= to_reverse[i];
        }
        vector<int> ans(n);
        iota(ans.begin(), ans.end(), 1);
        for (int i = n - 2; ~i; i--) {
            reverse(ans.end() - to_reverse[i] - 1, ans.end());
        }
        for (int i : ans) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}
