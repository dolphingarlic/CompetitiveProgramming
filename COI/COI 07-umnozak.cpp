/*
COI 2007 Umnozak
- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2008/olympiad_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll primes[4] = {2, 3, 5, 7}, LIM = 1e9;

ll A, B, A_lim, B_lim, dp[19][5200];
vector<ll> all_prods;
unordered_map<ll, ll> idx;

void generate(ll ptr = 0, ll prod = 1) {
    if (ptr == 4) {
        all_prods.push_back(prod);
        return;
    }
    while (prod <= LIM) {
        generate(ptr + 1, prod);
        prod *= primes[ptr];
    }
}

ll calculate(ll prefix, ll digits_left, ll prod) {
    ll mn = prefix, mx = prefix;
    for (ll i = 0; i < digits_left; i++) mn *= 10, mx = mx * 10 + 9;

    if (mn > B_lim || mx < A_lim) return 0;
    if (!digits_left) return (prod == 1);

    if (mn >= A_lim && mx <= B_lim && ~dp[digits_left][idx[prod]])
        return dp[digits_left][idx[prod]];

    ll ans = 0;
    for (ll i = 1; i < 10; i++) if (prod % i == 0)
        ans += calculate(prefix * 10 + i, digits_left - 1, prod / i);

    if (mn >= A_lim && mx <= B_lim) return dp[digits_left][idx[prod]] = ans;
    return ans;
}

int main() {
    scanf("%lld %lld", &A, &B);

    memset(dp, -1, sizeof(dp));
    generate();

    ll ans = 0;
    for (ll i = 0; i < all_prods.size(); i++) idx[all_prods[i]] = i;
    for (ll i : all_prods) {
        A_lim = A / i, B_lim = B / i;
        if (A % i) A_lim++;
        for (ll j = 1; j < 19; j++) ans += calculate(0, j, i);
    }
    printf("%lld\n", ans);
    return 0;
}