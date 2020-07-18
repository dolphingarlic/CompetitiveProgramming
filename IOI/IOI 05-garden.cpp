/*
IOI 2005 Garden
- Firstly, notice that there must be some line separating the 2 gardens
- This lets us reduce the problem into a simpler one: given a prefix/suffix
  of the rows/columns, what is the minimum perimeter for 1 good garden?
- Firstly, we use 2D prefix sums so we can quickly find the number of roses
  in any given rectangle
- Next, we can binary search for the smallest rectangle with K roses given
  one of its edges
    - There are O(LW(L + W)) edges in an L by W rectangle
- Finally, we collect all these minimums and find the solution using DP
- Complexity: O(LW(L + W) log L)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int pref[252][252], top[252], bot[252], lef[252], rig[252];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int l, w, n, k;
    cin >> l >> w >> n >> k;
    while (n--) {
        int x, y;
        cin >> x >> y;
        pref[x][y]++;
    }
    memset(top, 0x3f, sizeof top), memset(bot, 0x3f, sizeof bot);
    memset(lef, 0x3f, sizeof lef), memset(rig, 0x3f, sizeof rig);

    FOR(i, 1, l + 1) FOR(j, 1, w + 1) pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];

    FOR(i, 1, l + 1) FOR(j, 1, w + 1) {
        FOR(x, 0, i) {
            int l = 0, r = j - 1;
            while (l != r) {
                int y = (l + r + 1) / 2;
                int perim = i + j - y - x, roses = pref[i][j] + pref[x][y] - pref[i][y] - pref[x][j];
                if (roses >= k) l = y;
                else r = y - 1;
                if (roses == k) {
                    top[i] = min(top[i], perim);
                    lef[j] = min(lef[j], perim);
                }
            }
            int y = l;
            int perim = i + j - y - x, roses = pref[i][j] + pref[x][y] - pref[i][y] - pref[x][j];
            if (roses == k) {
                top[i] = min(top[i], perim);
                lef[j] = min(lef[j], perim);
            }
        }
        FOR(x, i, l + 1) {
            int l = j, r = w;
            while (l != r) {
                int y = (l + r) / 2;
                int perim = x + y - i - j + 2, roses = pref[x][y] + pref[i - 1][j - 1] - pref[i - 1][y] - pref[x][j - 1];
                if (roses >= k) r = y;
                else l = y + 1;
                if (roses == k) {
                    bot[i - 1] = min(bot[i - 1], perim);
                    rig[j - 1] = min(rig[j - 1], perim);
                }
            }
            int y = l;
            int perim = x + y - i - j + 2, roses = pref[x][y] + pref[i - 1][j - 1] - pref[i - 1][y] - pref[x][j - 1];
            if (roses == k) {
                bot[i - 1] = min(bot[i - 1], perim);
                rig[j - 1] = min(rig[j - 1], perim);
            }
        }
    }

    FOR(i, 1, l + 1) top[i] = min(top[i], top[i - 1]), bot[l - i + 1] = min(bot[l - i + 1], bot[l - i + 2]);
    FOR(i, 1, w + 1) lef[i] = min(lef[i], lef[i - 1]), rig[w - i + 1] = min(rig[w - i + 1], rig[w - i + 2]);

    int ans = 0x3f3f3f3f;
    FOR(i, 1, l + 1) ans = min(ans, top[i] + bot[i]);
    FOR(i, 1, w + 1) ans = min(ans, lef[i] + rig[i]);
    if (ans == 0x3f3f3f3f) cout << "NO";
    else cout << 2 * ans;
    return 0;
}