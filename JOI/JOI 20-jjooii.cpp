/*
JOI 2020 JJOOII
- For each starting point...
    - Find the next point such that the number of "J"s between it and the starting
      point is equal to K
    - Find the next point such that the number of "O"s between it and the previous
      point is equal to K
    - Find the next point such that the number of "I"s between it and the previous
      point is equal to K
    - Notice how this is always optimal because we want to minimize the distance
      between the first and last points
- We can use 4 pointers and prefix sums to find the 4 points for each starting point
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int pref[4][200001], ptr[4];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    string s;
    cin >> n >> k >> s;
    FOR(i, 0, n) {
        FOR(j, 1, 4) pref[j][i + 1] = pref[j][i];
        if (s[i] == 'J') pref[1][i + 1]++;
        if (s[i] == 'O') pref[2][i + 1]++;
        if (s[i] == 'I') pref[3][i + 1]++;
    }

    int ans = INT_MAX;
    for (ptr[0] = 0; ptr[0] <= n; ptr[0]++) {
        FOR(i, 1, 4)
            while (ptr[i] < ptr[i - 1] || (ptr[i] <= n && pref[i][ptr[i]] - pref[i][ptr[i - 1]] < k))
                ptr[i]++;
        bool possible = true;
        FOR(i, 1, 4) if (ptr[i] > n || pref[i][ptr[i]] - pref[i][ptr[i - 1]] < k) possible = false;
        if (possible) ans = min(ans, ptr[3] - ptr[0] - 3 * k);
    }
    if (ans == INT_MAX) cout << -1;
    else cout << ans;
    return 0;
}