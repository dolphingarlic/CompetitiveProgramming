/*
CEOI 2013 Adriatic
- dp[i][j] = Minimum no. of jumps to visit all islands in the rectangle (i, j) to (N, 1)
           = 0 if there are no islands in the rectangle;
             pref[i][j] + dp[Max row with column less than j][Min column with row greater than i] otherwise
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

pair<int, int> island[250001];
int pref[2501][2501];
ll dp[2501][2501];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        pref[x][y] = 1;
        island[i] = {x, y};
    }
    return 0;
}