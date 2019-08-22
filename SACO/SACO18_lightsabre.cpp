// C++ program to find minimum
// number of trials in worst case.
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// Find sum of binomial coefficients xCi
// (where i varies from 1 to n). If the sum
// becomes more than K
ll binomialCoeff(ll x, ll n, ll k) {
    ll sum = 0, term = 1;
    for (ll i = 1; i <= n && sum < k; ++i) {
        term *= x - i + 1;
        term /= i;
        sum += term;
    }
    return sum;
}

// Do binary search to find minimum
// number of trials in worst case.
ll mllrials(ll n, ll k) {
    // Initialize low and high as 1st
    // and last floors
    ll low = 1, high = k;

    // Do binary search, for every mid,
    // find sum of binomial coefficients and
    // check if the sum is greater than k or not.
    while (low < high) {
        ll mid = (low + high) / 2;
        if (binomialCoeff(mid, n, k) < k)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

/* Drier program to test above function*/
int main() {
    ll n, m;
    cin >> n >> m;
    cout << mllrials(m, n) << '\n';
    return 0;
}