/*
EOI 2019 Sum
- If N * (N + 1) / 2 < S, it's not possible
- Construct the sum greedily otherwise
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll n, s;
        cin >> n >> s;
        if (n * (n + 1) / 2 < s) cout << "-1\n";
        else {
            vector<ll> ans;
            for (int i = n; s > i; i--) {
                ans.push_back(i);
                s -= i;
            }
            ans.push_back(s);
            cout << ans.size() << ' ';
            for (int i : ans) cout << i << ' ';
            cout << '\n';
        }
    }
    return 0;
}