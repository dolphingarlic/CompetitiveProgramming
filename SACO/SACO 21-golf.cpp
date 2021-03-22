#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int B = 1000;

int h[1000000], has[1000000];
set<int> s[1000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        has[h[i]] = i;
        s[i / B].insert(h[i]);
        if (s[i / B].size() == 19) s[i / B].erase(s[i / B].begin());
    }
    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;
        l--, r--;
        set<int> best;
        for (int i = 0; i * B < n; i++) {
            if (i * B >= l && i * B + B - 1 <= r) {
                for (int j : s[i]) {
                    best.insert(i);
                    if (best.size() == 19) best.erase(best.begin());
                }
            } else if (l >= i * B && r <= i * B + B - 1) {
                for (int j = l; j <= r; j++) {
                    best.insert(h[j]);
                    if (best.size() == 19) best.erase(best.begin());
                }
            } else if (i * B + B - 1 >= l && i * B < l) {
                for (int j = l; j < i * B + B; j++) {
                    best.insert(h[j]);
                    if (best.size() == 19) best.erase(best.begin());
                }
            } else if (i * B <= r && i * B + B - 1 > r) {
                for (int j = i * B; j <= r; j++) {
                    best.insert(h[j]);
                    if (best.size() == 19) best.erase(best.begin());
                }
            }
        }
        for (int i = 1; i < k; i++) best.erase(*best.rbegin());
        cout << has[*best.rbegin()] + 1 << '\n';
    }
    return 0;
}
