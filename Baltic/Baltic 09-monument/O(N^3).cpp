#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bool block[3][151][151][151];
int dp[151][151][151], prv[151], nxt[151];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int r, s, t;
    cin >> r >> s >> t;
    swap(r, s);
    FOR(x, 1, r + 1) FOR(y, 1, s + 1) FOR(z, 1, t + 1) {
        char c;
        cin >> c;
        block[0][x][y][z] = block[1][y][z][x] = block[2][z][x][y] = (c == 'N');
    }

    int ans = 0;
    FOR(dim, 0, 3) {
        FOR(x, 1, r + 1) FOR(y, 1, s + 1) FOR(z, 1, t + 1) {
            dp[x][y][z] = 0;
            if (block[dim][x][y][z]) {
                dp[x][y][z] = min(dp[x - 1][y - 1][z], min(dp[x - 1][y][z], dp[x][y - 1][z])) + 1;
            }
        }

        FOR(x, 1, r + 1) FOR(y, 1, s + 1) {
            stack<int> stck;
            FOR(z, 1, t + 1) {
                while (stck.size() && dp[x][y][stck.top()] >= dp[x][y][z]) stck.pop();
                if (stck.size()) prv[z] = stck.top() + 1;
                else prv[z] = 1;
                stck.push(z);
            }
            while (stck.size()) stck.pop();
            for (int z = t; z; z--) {
                while (stck.size() && dp[x][y][stck.top()] >= dp[x][y][z]) stck.pop();
                if (stck.size()) nxt[z] = stck.top() - 1;
                else nxt[z] = t;
                stck.push(z);
            }

            FOR(z, 1, t + 1) ans = max(ans, dp[x][y][z] * (nxt[z] - prv[z] + 1));
        }

        swap(r, s);
        swap(s, t);
    }

    cout << ans * 4;
    return 0;
}