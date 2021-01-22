#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll pow_9[19]{1};

ll calc(ll x) {
    if (x == -1) return 0;
    ll ans = 0;
    vector<int> digits;
    while (x) {
        digits.push_back(x % 10);
        x /= 10;
    }
    for (int i = 0; i < digits.size() - 1; i++) ans += pow_9[i];
    digits.push_back(10);
    for (int i = digits.size() - 2; ~i; i--) {
        ans += digits[i] * pow_9[i];
        if (digits[i] > digits[i + 1]) ans -= pow_9[i];

        if (digits[i] == digits[i + 1]) return ans;
    }
    return ans + 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    for (int i = 1; i <= 18; i++) pow_9[i] = 9 * pow_9[i - 1];
    ll a, b;
    cin >> a >> b;
    cout << calc(b) - calc(a - 1);
    return 0;
}