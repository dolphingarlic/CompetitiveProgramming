#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Object {
    int c;
    ll f, v;
    bool operator<(Object B) {
        if (f == B.f) return v > B.v;
        return f < B.f;
    }
} obj[4001];

ll dp[100005];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n;
    FOR(i, 0, n) {
        cin >> obj[i].c >> obj[i].f >> obj[i].v;
        obj[i].v *= -1;
    }
    cin >> m;
    FOR(i, n, n + m) {
        cin >> obj[i].c >> obj[i].f >> obj[i].v;
        obj[i].c *= -1;
    }
    sort(obj, obj + n + m);

    int mx = 0;
    FOR(i, 0, n + m) {
        if (obj[i].v > 0) {
            for (int j = mx; ~j; j--)
                dp[j - obj[i].c] = max(dp[j - obj[i].c], dp[j] + obj[i].v);
            mx -= obj[i].c;
        } else {
            FOR(j, 1, obj[i].c)
                dp[0] = max(dp[0], dp[j] + obj[i].v);
            FOR(j, obj[i].c, mx + 1)
                dp[j - obj[i].c] = max(dp[j - obj[i].c], dp[j] + obj[i].v);
        }
    }

    cout << dp[0];
    return 0;
}