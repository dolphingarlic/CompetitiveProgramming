/*
CEOI 2006 Connect
- There are only 11 types of filled-in cells:
    +.+  + +  + +  + +  +.+  +.+  +.+  + +  + +  + +  + +
     X    X.   X   .X    ..   .   ..    ..  ...  ..
    + +  + +  +.+  + +  + +  +.+  + +  +.+  + +  +.+  + +
    0    1    2    3    4    5    6    7    8    9    10
- Also, we only care about a "broken profile" of N+1 **corridors**
- Let dp[i][j][mask] = The minimum cost to get a broken profile specified by mask
                       if we've processed cells (by column) up to cell (i, j)
- Then it's just a lot of casework; see code for details
- We can use backtracking to reconstruct the grid
- Complexity: If N = R/2 and M = C/2, O(NM 2^(N + 1))
*/

#include <bits/stdc++.h>
using namespace std;

struct State {
    State *prv;
    int cost, type;

    State(int _cost = 10000) : prv(nullptr), cost(_cost), type(-1) {}
    State(State *_prv, int _type) : prv(_prv), type(_type), cost(_prv->cost) {
        if (type < 4) cost++;
        else if (type < 10) cost += 2;
    }
};

State *construct(State *A, int typeA, State *B = nullptr, int typeB = -1) {
    if (!A && !B) return nullptr;
    if (!A) return new State(B, typeB);
    if (!B) return new State(A, typeA);
    if (A->cost < B->cost) return new State(A, typeA);
    return new State(B, typeB);
}

string grid[25];
State *dp[12][40][1 << 13];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int r, c;
    cin >> r >> c;
    getline(cin, grid[0]); // Buffer stuff >:(
    for (int i = 0; i < r; i++) getline(cin, grid[i]);
    int n = r >> 1, m = c >> 1;

    dp[n - 1][0][0] = new State(0);
    for (int j = 1; j <= m; j++) {
        for (int i = 0; i < n; i++) {
            for (int mask = 0; mask < (1 << n + 1); mask++) {
                int r = mask & (1 << i), d = mask & (1 << i + 1);
                // You can't connect over a blocked corridor
                if (r && grid[2 * i + 1][2 * j] == '|') continue;
                if (d && grid[2 * i + 2][2 * j - 1] == '-') continue;
                // An 'X' can't have more than 1 paths going out from it
                if (r && d && grid[2 * i + 1][2 * j - 1] == 'X') continue;
                // Casework for the DP
                if (!i) {
                    int prv_base = (mask >> 2) << 1;
                    if (grid[2 * i + 1][2 * j - 1] == 'X') {
                        if (r || d) {
                            if (r) dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base], 1);
                            if (d) dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base], 2);
                        } else dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base + 1], 3);
                    } else {
                        if (r && d) dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base], 7);
                        else if (r || d) {
                            if (r) dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base + 1], 8);
                            if (d) dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base + 1], 9);
                        } else dp[i][j][mask] = construct(dp[n - 1][j - 1][prv_base], 10);
                    }
                } else {
                    int prv_base = mask & (((1 << n + 1) - 1) ^ (1 << i) + (1 << i + 1));
                    if (grid[2 * i + 1][2 * j - 1] == 'X') {
                        if (r || d) {
                            if (r) dp[i][j][mask] = construct(dp[i - 1][j][prv_base], 1);
                            if (d) dp[i][j][mask] = construct(dp[i - 1][j][prv_base], 2);
                        } else dp[i][j][mask] = construct(
                                dp[i - 1][j][prv_base + (1 << i)], 0,
                                dp[i - 1][j][prv_base + (1 << i + 1)], 3);
                    } else {
                        if (r && d) dp[i][j][mask] = construct(dp[i - 1][j][prv_base], 7);
                        else if (r || d) {
                            if (r) dp[i][j][mask] = construct(
                                    dp[i - 1][j][prv_base + (1 << i)], 4,
                                    dp[i - 1][j][prv_base + (1 << i + 1)], 8);
                            if (d) dp[i][j][mask] = construct(
                                    dp[i - 1][j][prv_base + (1 << i)], 5,
                                    dp[i - 1][j][prv_base + (1 << i + 1)], 9);
                        } else dp[i][j][mask] = construct(
                                dp[i - 1][j][prv_base + (1 << i) + (1 << i + 1)], 6,
                                dp[i - 1][j][prv_base], 10);
                    }
                }
            }
        }
    }
    cout << dp[n - 1][m][0]->cost << '\n';
    State *curr = dp[n - 1][m][0];
    for (int j = m - 1; ~j; j--) for (int i = n - 1; ~i; i--) {
        if (curr->type == 0) grid[2 * i][2 * j + 1] = '.';
        else if (curr->type == 1) grid[2 * i + 1][2 * j + 2] = '.';
        else if (curr->type == 2) grid[2 * i + 2][2 * j + 1] = '.';
        else if (curr->type == 3) grid[2 * i + 1][2 * j] = '.';
        else if (curr->type == 4) grid[2 * i][2 * j + 1] = grid[2 * i + 1][2 * j + 1] = grid[2 * i + 1][2 * j + 2] = '.';
        else if (curr->type == 5) grid[2 * i][2 * j + 1] = grid[2 * i + 1][2 * j + 1] = grid[2 * i + 2][2 * j + 1] = '.';
        else if (curr->type == 6) grid[2 * i][2 * j + 1] = grid[2 * i + 1][2 * j + 1] = grid[2 * i + 1][2 * j] = '.';
        else if (curr->type == 7) grid[2 * i + 1][2 * j + 2] = grid[2 * i + 1][2 * j + 1] = grid[2 * i + 2][2 * j + 1] = '.';
        else if (curr->type == 8) grid[2 * i + 1][2 * j + 2] = grid[2 * i + 1][2 * j + 1] = grid[2 * i + 1][2 * j] = '.';
        else if (curr->type == 9) grid[2 * i + 2][2 * j + 1] = grid[2 * i + 1][2 * j + 1] = grid[2 * i + 1][2 * j] = '.';
        curr = curr->prv;
    }
    for (int i = 0; i < r; i++) cout << grid[i] << '\n';
    return 0;
}
