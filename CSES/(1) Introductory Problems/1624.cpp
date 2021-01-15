#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int ans = 0;
char board[8][8];
bool visited[8], diag_l[16], diag_r[16];
 
void dfs(int curr, int depth) {
    visited[curr] = true;
    diag_l[curr - depth + 7] = true;
    diag_r[curr + depth] = true;
 
    if (depth == 7) ans++;
    else {
        FOR(i, 0, 8) {
            if (board[depth + 1][i] == '.' && !visited[i] && !diag_l[i - depth + 6] && !diag_r[i + depth + 1]) {
                dfs(i, depth + 1);
            }
        }
    }
 
    visited[curr] = false;
    diag_l[curr - depth + 7] = false;
    diag_r[curr + depth] = false;
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    FOR(i, 0, 8) FOR(j, 0, 8) cin >> board[i][j];
    FOR(i, 0, 8) if (board[0][i] == '.') dfs(i, 0);
    cout << ans;
    return 0;
}