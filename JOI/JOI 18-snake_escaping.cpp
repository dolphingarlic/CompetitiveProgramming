/*
JOI 2018 Snake Escaping
- Let A = number of '?'s, B = number of '0's, and C = number of '1's
- Algorithm 1: O(2^A)
    - Just iterate through every possible bitmask the '?'s can make
- Algorithm 2: O(2^B)
    - We use SOS DP and PIE by iterating over the mask of '0's
    - Here, we do a "reverse" SOS DP i.e. we flip the bits
- Algorithm 3: O(2^C)
    - Same as algorithm 2, but we use a normal SOS DP and we iterate over the mask of '1's
- Just pick which algorithm works fastest for each query
- Complexity: O(L * 2^L + Q * 2^(L/3))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int l, q, a, b, c, sos[1 << 20], rsos[1 << 20];
string s, k;

int solve_a() { // Brute force over '?'
    int ans = 0, base = 0, mask = 0;
    FOR(i, 0, l) {
        if (k[i] == '?') mask += 1 << i;
        else if (k[i] == '1') base += 1 << i;
    }
    for (int i = mask; i; i = mask & (i - 1)) ans += s[i | base] - '0';
    ans += s[base] - '0';
    return ans;
}

int solve_b() { // Brute force over '0'
    int ans = 0, base = 0, mask = 0;
    FOR(i, 0, l) {
        if (k[i] == '0') mask += 1 << i;
        else if (k[i] == '?') base += 1 << i;
    }
    for (int i = mask; i; i = mask & (i - 1)) ans += ((b - __builtin_popcount(i)) & 1 ? -1 : 1) * rsos[i | base];
    ans += (b & 1 ? -1 : 1) * rsos[base];
    return ans;
}

int solve_c() { // Brute force over '1'
    int ans = 0, base = 0, mask = 0;
    FOR(i, 0, l) {
        if (k[i] == '1') mask += 1 << i;
        else if (k[i] == '?') base += 1 << i;
    }
    for (int i = mask; i; i = mask & (i - 1)) ans += ((c - __builtin_popcount(i)) & 1 ? -1 : 1) * sos[i | base];
    ans += (c & 1 ? -1 : 1) * sos[base];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> l >> q >> s;
    FOR(i, 0, 1 << l) sos[i] = s[i] - '0', rsos[i] = s[(1 << l) - i - 1] - '0';
    FOR(i, 0, l) FOR(j, 0, (1 << l)) if (j & (1 << i))
        sos[j] += sos[j ^ (1 << i)], rsos[j] += rsos[j ^ (1 << i)];

    while (q--) {
        cin >> k;
        reverse(k.begin(), k.end());
        a = b = c = 0;
        FOR(i, 0, l) {
            if (k[i] == '?') a++;
            if (k[i] == '0') b++;
            if (k[i] == '1') c++;
        }
        
        if (a < 7) cout << solve_a() << '\n';
        else if (b < 7) cout << solve_b() << '\n';
        else cout << solve_c() << '\n';
    }
    return 0;
}