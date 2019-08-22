#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

bitset<100000001> not_prime;
void gen_primes(int n) {
    not_prime[1] = 1;
    for (int i = 4; i <= n; i += 2) not_prime[i] = 1;
    for (int i = 3; i <= n; i += 2) {
        if (not_prime[i] == 0) for (int j = 2 * i; j <= n; j += i) not_prime[j] = 1;
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    gen_primes(n + 1);

    ll ans = 1;
    for (int i = 2; i <= n; i += 4) {
        bool is = true;
        FOR(j, 1, (int)sqrt(i) + 1) {
            if (i % j == 0 && not_prime[j + i / j] == 1) {
                is = false;
                break;
            }
        }
        if (is) ans += i;
    }

    cout << ans;
    return 0;
}