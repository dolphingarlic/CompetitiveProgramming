/*
COCI 2016 Vjestica
- Firstly, notice that N is very small. This implies that we should use a bitmask
- For each mask, we split the active words into 2 groups and solve recursively for those if it has more than 1 bit
- If it has only 1 bit, the size of the trie is simply the number of letters in that word
- solve(mask) = min(solve(A) + solve(B)) where A + B = mask, A & mask == A, B & mask == B, and A & B == 0
- To do this efficiently, we iterate over all submasks of mask
- Complexity: O(3^N)
*/

#include <bits/stdc++.h>
using namespace std;

int n, dp[1 << 16];
map<char, int> cnt[16];

int get_pref(int mask) {
    map<char, int> pref;
    int ans = 0;
    for (char j = 'a'; j <= 'z'; j++) {
        pref[j] = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) pref[j] = min(pref[j], cnt[i][j]);
        }
        ans += pref[j];
    }
    return ans;
}

void solve(int mask) {
    int pref = get_pref(mask);
    if (__builtin_popcount(mask) == 1) dp[mask] = pref;
    else {
        dp[mask] = INT_MAX;
        for (int i = mask & (mask - 1); i; i = mask & (i - 1)) {
            dp[mask] = min(dp[mask], dp[i] + dp[mask ^ i] - pref);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (char j = 'a'; j <= 'z'; j++) cnt[i][j] = 0;
        string s;
        cin >> s;
        for (char j : s) cnt[i][j]++;
    }

    for (int i = 1; i < (1 << n); i++) solve(i);

    cout << dp[(1 << n) - 1] + 1;
    return 0;
}