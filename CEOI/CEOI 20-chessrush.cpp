/*
CEOI 2020 Chessrush
- Pawns
    - There's only either 0 or 1 possible fixed-length paths
    - O(1)
- Rooks
    - If the start and end columns are equal, there's 1 path of length 1
    - Otherwise, there are 2 paths of length 2
    - O(1)
- Queens
    - If the start and end columns or diagonals are equal, there's
      1 path of length 1
    - Otherwise, there are at least 4 paths of length 2
        - If the start or end column is at an extremity and the board is
          square, add a path
        - If the start and end squares are the same colour and the queen
          can travel on two diagonals to reach the end, add a path
    - O(1)
- Bishops
    - If the start and end squares are the same colour, then there's at
      least 1 path
    - Consider what happens if we just wildly bounce around between sides
    - We might miss the end block, but this is at most 1 move less than
      the optimal path
    - If we cut the last bounce early, we'll hit the desired square
        - Let's say we cut it F blocks early, and it took N moves
    - We can distribute these F blocks amongst the first N - 1 moves
        - Not the Nth move because that can't be cut short
    - The number of ways to do this is (F + N - 2 choose F)
    - We can compute this values naively because F is small
    - O(QC)
- Kings
    - There's always at least 1 fixed-length path
    - dp[i][j][m - 1] = Ways to go from cell (1, i) to cell (m - 1, j)
                      = dp[i][j - 1][m - 2] + dp[i][j][m - 2] + dp[i][j + 1][m - 2]
                      = sum(dp[i][k][m / 2] * dp[k][j][m / 2])
    - We can optimize this by doing the following:
        - First, compute all dp[1][j] and dp[i][1] in O(C^2)
        - Next, use the recurrence dp[i][j] = dp[i - 1][j - 1] + dp[1][i + j - 1]
            - Clearly, i + j <= C + 1
        - Finally, use symmetries to fill in the rest of the DP values
    - O(C^2 log R)
*/

#include <bits/stdc++.h>

#include "arithmetics.h"
using namespace std;

pair<int, int> solve_bishop(int x, int y, int r, int c) {
    int moves = 1 + (r - x + c - 2) / (c - 1);
    x--, y--;
    int end_col = 1 + (r - x + c - 3) % (c - 1);
    if (moves & 1) y = c - y - 1;
    int rem;
    if (end_col <= y)
        rem = (y - end_col) / 2;
    else {
        moves++;
        rem = c - 1 - (end_col + y) / 2;
    }
    int ways = 1;
    for (int i = 1; i <= rem; i++)
        ways = Div(Mul(ways, moves + rem - 1 - i), i);
    return {moves, ways};
}

int dp[1002][1002], nxt[1002][1002];

void precompute_king(int r, int c) {
    vector<vector<int>> nxt(c + 2, vector<int>(c + 2, 0));
    if (r == 2) {
        for (int i = 1; i <= c; i++)
            nxt[i][i - 1] = nxt[i][i] = nxt[i][i + 1] = 1;
        for (int i = 1; i <= c; i++)
            nxt[i][0] = nxt[i][c + 1] = nxt[0][i] = nxt[c + 1][i] = 0;
    } else if (r & 1) {
        precompute_king(r / 2 + 1, c);
        for (int j = 1; j <= c; j++)
            for (int k = 1; k <= c; k++) {
                nxt[1][j] = Add(nxt[1][j], Mul(dp[1][k], dp[k][j]));
                nxt[j][1] = nxt[1][j];
            }
        for (int i = 2; i <= c; i++)
            for (int j = 2; j <= c; j++)
                if (i + j <= c + 1)
                    nxt[i][j] = Add(nxt[i - 1][j - 1], nxt[1][i + j - 1]);
        for (int i = 2; i <= c; i++)
            for (int j = 2; j <= c; j++)
                if (i + j > c + 1)
                    nxt[i][j] = nxt[c + 1 - i][c + 1 - j];
    } else {
        precompute_king(r - 1, c);
        for (int i = 1; i <= c; i++)
            for (int j = 1; j <= c; j++)
                nxt[i][j] = Add(dp[i][j - 1], Add(dp[i][j], dp[i][j + 1]));
    }
    for (int i = 1; i <= c; i++)
        for (int j = 1; j <= c; j++)
            dp[i][j] = nxt[i][j];
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int r, c, q;
    cin >> r >> c >> q;
    precompute_king(r, c);
    while (q--) {
        char p;
        int x, y;
        cin >> p >> x >> y;
        switch (p) {
            case 'P':
                if (x == y)
                    cout << r - 1 << " 1\n";
                else
                    cout << "0 0\n";
                break;
            case 'R':
                if (x == y)
                    cout << "1 1\n";
                else
                    cout << "2 2\n";
                break;
            case 'Q':
                if (x == y || x + r - 1 == y || x - r + 1 == y)
                    cout << "1 1\n";
                else {
                    int ways = 4;
                    // Extremities
                    if (r == c && (y == 1 || y == r || x == 1 || x == r))
                        ways++;
                    if (x + y + r & 1) {
                        // Double diagonal
                        if (r - x < y) ways++;
                        if (r - c + x - 1 < c - y + 1) ways++;
                    }
                    cout << "2 " << ways << '\n';
                }
                break;
            case 'B':
                if (x + y + r & 1) {
                    if (r == c && ((x == 1 && y == c) || (x == c && y == 1)))
                        cout << "1 1\n";
                    else {
                        pair<int, int> move_left = solve_bishop(x, y, r, c);
                        pair<int, int> move_right =
                            solve_bishop(c - x + 1, c - y + 1, r, c);
                        if (move_left.first > move_right.first)
                            move_left = move_right;
                        else if (move_left.first == move_right.first) {
                            move_left.second = Add(move_left.second, move_right.second);
                        }
                        cout << move_left.first << ' ' << move_left.second
                             << '\n';
                    }
                } else
                    cout << "0 0\n";
                break;
            case 'K':
                cout << r - 1 << ' ' << dp[x][y] << '\n';
                break;
        }
    }
    return 0;
}
