#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int l_cnt[1001], r_cnt[1002], a[20001], ans = 0;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int m, n;
    cin >> m >> n;
    FOR(i, 1, n + 1) cin >> a[i];

    int lptr = 1, rs = 1, re = 2;
    FOR(i, 1, n / 2 + 1) {
        l_cnt[a[lptr++]]++;
        r_cnt[a[rs++]]--;
        FOR(j, re - 1, re + 1) r_cnt[a[j]]++;
        re += 2;

        int available = 0;
        bool possible = true;
        for (int j = m; j > 0; j--) {
            available += r_cnt[j + 1];
            available -= l_cnt[j];
            if (available < 0) {
                possible = false;
                break;
            }
        }

        if (possible) ans = i;
    }

    cout << ans;
    return 0;
}