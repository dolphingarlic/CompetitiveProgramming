/*
Baltic 2008 Grid
- Binary search for the answer
- When checking the answer, check each combination of R parallels (there are O(2^N) of them) and sweep from
  left to right
    - Whenever a block between the last meridian and the current sweep position has a computation time exceeding
      the value we're checking, greedily draw a new meridian there
    - The value is good iff any combination results in at most C meridians drawn
- We can use 2D prefix sums to get range sum queries
- Complexity: O(M * 2^N log ANS)
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, r, c, pref[19][19];

int tot(int x1, int y1, int x2, int y2) {
    return pref[x2][y2] + pref[x1 - 1][y1 - 1] - pref[x2][y1 - 1] - pref[x1 - 1][y2];
}

bool check(int mx) {
    for (int mask = 0; mask < (1 << n); mask++) if (!(mask & 1) && __builtin_popcount(mask) == r) {
        bool good = true;
        vector<int> parallels = {0};
        for (int i = 1; i < n; i++) if (mask & (1 << i)) parallels.push_back(i);
        parallels.push_back(n);
        int last_meridian = 0, cnt = 0;
        for (int i = 0; i < m; i++) {
            int mx_tot = 0;
            for (int j = 1; j <= r + 1; j++)
                mx_tot = max(mx_tot, tot(parallels[j - 1] + 1, last_meridian + 1, parallels[j], i + 1));
            if (mx_tot > mx) {
                if (i == last_meridian) {
                    good = false;
                    break;
                } else last_meridian = i--, cnt++;
            }
        }
        good &= cnt <= c;
        if (good) return true;
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m >> r >> c;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) {
        cin >> pref[i][j];
        pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
    }
    int l = 0, r = pref[n][m];
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}
