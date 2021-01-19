/*
COCI 2021 Vepar
- First, generate all the primes using the Sieve of Eratosthenes
- There are O(log N) primes (i.e. not that many)
- For each query, we can find its prime factorisation by checking the number of
  multiples of prime powers contained in the ranges
- Complexity: O(Good enough)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MX = 1e7;

bitset<MX> is_composite;
vector<ll> primes;

void sieve(ll ub) {
    for (ll i = 2; i <= ub; i++) {
        if (!is_composite[i]) {
            primes.push_back(i);
            for (ll j = i * 2; j <= MX; j += i) is_composite[j] = 1;
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    sieve(MX);
    while (t--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        bool good = true;
        for (ll i : primes) {
            ll j = i, cnt_1 = 0, cnt_2 = 0;
            while (j <= b) {
                cnt_1 += b / j - (a - 1) / j;
                j *= i;
            }
            j = i;
            while (j <= d) {
                cnt_2 += d / j - (c - 1) / j;
                j *= i;
            }
            if (cnt_2 < cnt_1) {
                good = false;
                break;
            }
        }
        cout << (good ? "DA\n" : "NE\n");
    }
    return 0;
}
