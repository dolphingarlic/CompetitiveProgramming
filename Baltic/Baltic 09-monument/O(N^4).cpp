#include <iostream>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

char c[151][151][151];
bool block[3][151][151][151];
int dp[151][151][151];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int r, s, t;
    cin >> r >> s >> t;
    swap(r, s);
    FOR(x, 1, r + 1) FOR(y, 1, s + 1) FOR(z, 1, t + 1) cin >> c[x][y][z];
    FOR(x, 1, r + 1) FOR(y, 1, s + 1) FOR(z, 1, t + 1) block[0][x][y][z] = block[1][y][z][x] = block[2][z][x][y] = (c[x][y][z] == 'N');

    int ans = 0;
    FOR(dim, 0, 3) {
        FOR(x, 1, r + 1) FOR(y, 1, s + 1) dp[x][y][1] = 0;
        FOR(z, 1, t + 1) FOR(x, 1, r + 1) FOR(y, 1, s + 1) {
            if (block[dim][x][y][z]) dp[x][y][1]++;
            else dp[x][y][1] = 0;

            FOR(w, 2, min(x, y) + 1) {
                dp[x][y][w] = min(min(dp[x][y][w - 1], dp[x - 1][y][w - 1]), min(dp[x][y - 1][w - 1], dp[x - 1][y - 1][w - 1]));
                ans = max(ans, dp[x][y][w] * w);
            }
        }
        swap(r, s);
        swap(s, t);
    }

    cout << ans * 4;
    return 0;
}