#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef unsigned long long ll;
using namespace std;

const ll P = 29;

ll pw[1000001]{1};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    FOR(i, 1, 1000001) pw[i] = pw[i - 1] * P;

    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int l = 0, r = s.size() - 1, pl = 0, pr = s.size() - 1;
        int ans = 0;
        ll hsh_l = 0, hsh_r = 0;

        while (l < r) {
            hsh_l = hsh_l * P + (s[l++] - 'a' + 1);
            hsh_r += pw[pr - r] * (s[r--] - 'a' + 1);
            if (hsh_l == hsh_r) {
                FOR(i, 0, l - pl) if (s[pl + i] != s[r + i]) continue;
                ans += 2;
                hsh_l = hsh_r = 0;
                pl = l, pr = r;
            }
        }
        if (l == r || pl != l) ans++;

        cout << ans << '\n';
    }
    return 0;
}