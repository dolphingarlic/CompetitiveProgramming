#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int bit[1025][1025];
int n;

void update(int x, int y, int val) {
    for (; x <= n; x += (x & (-x))) {
        for (int i = y; i <= n; i += (i & (-i))) {
            bit[x][i] += val;
        }
    }
}
int query(int x1, int y1, int x2, int y2) {
    int ans = 0;
    for (int i = x2; i; i -= (i & (-i))) {
        for (int j = y2; j; j -= (j & (-j))) {
            ans += bit[i][j];
        }
    }

    for (int i = x2; i; i -= (i & (-i))) {
        for (int j = y1 - 1; j; j -= (j & (-j))) {
            ans -= bit[i][j];
        }
    }
    for (int i = x1 - 1; i; i -= (i & (-i))) {
        for (int j = y2; j; j -= (j & (-j))) {
            ans -= bit[i][j];
        }
    }

    for (int i = x1 - 1; i; i -= (i & (-i))) {
        for (int j = y1 - 1; j; j -= (j & (-j))) {
            ans += bit[i][j];
        }
    }

    return ans;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int q;
    cin >> q >> n >> q;

    while (q != 3) {
        if (q == 1) {
            int x, y, val;
            cin >> x >> y >> val;
            update(x + 1, y + 1, val);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << query(x1 + 1, y1 + 1, x2 + 1, y2 + 1) << '\n';
        }

        cin >> q;
    }

    return 0;
}