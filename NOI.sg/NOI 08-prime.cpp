/*
NOI.sg 2008 Prime
- Sieve of Erastothenes
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bitset<100000001> not_prime;
vector<int> primes = {2};
void gen_primes(int n) {
    not_prime[1] = 1;
    for (int i = 4; i <= n; i += 2) not_prime[i] = 1;
    for (int i = 3; i <= n; i += 2) {
        if (!not_prime[i]) {
            for (int j = 2 * i; j <= n; j += i) not_prime[j] = 1;
            primes.push_back(i);
        }
    }
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    gen_primes(104760);
    cout << primes[n - 1];
    return 0;
}