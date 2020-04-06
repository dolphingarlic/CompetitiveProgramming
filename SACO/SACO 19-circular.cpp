#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<ll> cycle = {2};

ll pw(ll base, ll expo) {
    ll ans = 1;
    while (expo) {
        if (expo & 1) ans *= base;
        base *= base;
        expo >>= 1;
    }
    return ans;
}

bool isprime(ll k) {
    FOR(i, 2, sqrt(k) + 1) {
        if (k % i == 0) return false;
    }
    return true;
}

ll getlen(ll k) {
    ll ans = 0;
    while (k) {
        ans++;
        k /= 10;
    }
    return ans;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;

    ll curr = 3;
    for (ll i = 1; i < n; curr += 2) {
        if (isprime(curr)) {
            bool is = true;
            ll len = getlen(curr);
            ll temp = curr;

            FOR(j, 1, len) {
                temp = (temp % 10) * pw(10, len - 1) + temp / 10;
                if (!isprime(temp)) {
                    is = false;
                    break;
                }
            }

            if (is) {
                cycle.push_back(curr);
                i++;
            }
        }
    }

    cout << cycle[n - 1];
    return 0;
}