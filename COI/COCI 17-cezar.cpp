#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int cnt[12];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, res = 21;
    fill(cnt, cnt + 12, 4);
    cnt[10] = 12;
    cin >> n;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        res -= x;
        cnt[x]--;
    }

    int c = 0;
    FOR(i, 2, min(12, res + 1)) c += cnt[i];
    if (2 * c >= 52 - n) cout << "VUCI";
    else cout << "DOSTA";
    return 0;
}