// Reference: https://math.stackexchange.com/questions/48682/maximization-with-xor-operator

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[100001], all_xor = 0;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        all_xor ^= a[i];
    }
    for (int i = 0; i < n; i++) a[i] &= ~all_xor;

    for (int i = 59, j = 0; ~i; i--) {
        int k = j;
        // Find any a[k] with the i-th bit as 1
        while (k < n && !(a[k] & (1ll << i))) k++;
        if (k == n) continue;
        // "Pivot" to make the i-th bit of a[j] also 1
        if (k > j) a[j] ^= a[k];
        k = j + 1;
        while (k < n) {
            // If a[k] has the i-th bit as 1, then it gets XORed with a[j]
            // Otherwise, it stays the same
            a[k] = min(a[k], a[k] ^ a[j]);
            k++;
        }
        j++;
    }
    ll ans = 0;
    // Now that the position of the most significant bit is different for each a[i],
    // we can greedily take the max subset XOR
    for (int i = 0; i < n; i++) ans = max(ans, ans ^ a[i]);
    cout << ans * 2 + all_xor;
    return 0;
}
