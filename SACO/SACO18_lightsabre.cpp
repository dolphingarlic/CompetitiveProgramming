#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll binomialCoeff(ll x, ll n, ll k) {
    ll sum = 0, term = 1;
    for (ll i = 1; i <= n && sum < k; ++i) {
        term *= x - i + 1;
        term /= i;
        sum += term;
    }
    return sum;
}

ll mllrials(ll n, ll k) {
    ll low = 1, high = k;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (binomialCoeff(mid, n, k) < k)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

int main() {
    ll n, m;
    cin >> n >> m;
    cout << mllrials(m, n) << '\n';
    return 0;
}