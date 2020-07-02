/*
Baltic 2013 Vim
- Firstly, let U be the set of letters/positions in S that aren't `e` but
  are preceded by `e`
- Let T be the string we get from removing all `e` from S
- Notice that the answer is
  2 * (No. of `e` in S) + (Cost to visit every position in U in T)
    - This is true because...
        - Whenever we encounter an `e`, it's optimal to delete it
        - Whenever we delete an `e`, we go to the letter proceeding it
        - We can never land on an `e` using `fe`, so we have to visit everything
          in U at least once
        - From every position in U, we have to press `h` at least
          (No. of consecutive `e`s preceding it) times to delete all
          consecutive `e`s preceding it
        - This gives us a lowerbound for the answer
        - If we follow the strategy of
            - Get to a position in U
            - Delete all consecutive `e`s preceding it
          then we use exactly that many key presses, which gives us the upperbound

- Next, notice that we'll never press `h` twice on any position twice
- This means the path we take will only consist of 2 "shapes":
    - From A, jump to B and jump to C
    - From A, jump to B, press `h` several times, and jump to C

- p[i][c] = Minimum number of key presses where
    - We visit all underlined before i
    - We end with `fc`
        - The cursor ends up on or to the left of i
- q[i][c][d] = Minimum number of key presses where
    - We visit all underlined before i
    - We use `fc`
        - The cursor ends up on or to the left of i
    - We then use `h` several times
    - We end with `fd`
        - The cursor ends up on or to the left of i

- From here, we could do O(A * N^2) DP but that only gets us 60 points
- For 100 points, see https://boi2013.informatik-olympiade.de/wp-content/uploads/2013/05/vim-spoiler.pdf
- Complexity: O(A^2 * N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bool underlined[70000];
int t[70000], p[70000][10], q[70000][10][10];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, t_cnt = 0, e_cnt = 0;
    string s;
    cin >> n >> s;
    underlined[0] = true;
    t[t_cnt++] = s[0] - 'a';
    FOR(i, 1, n) {
        if (s[i] != 'e') {
            if (s[i - 1] == 'e') underlined[t_cnt] = true;
            t[t_cnt++] = s[i] - 'a';
        } else e_cnt++;
    }

    memset(q[0], 0x3f, sizeof q[0]);
    FOR(c, 0, 10) p[0][c] = (c == t[0] ? 0 : 2);
    
    FOR(i, 0, t_cnt) {
        FOR(c, 0, 10) {
            p[i + 1][c] = min(p[i][t[i]], q[i][t[i]][t[i]]) + 2;
            if (c != t[i]) {
                p[i + 1][c] = min(p[i + 1][c], q[i][t[i]][c]);
                if (!underlined[i]) p[i + 1][c] = min(p[i + 1][c], p[i][c]);
            }

            FOR(d, 0, 10) {
                q[i + 1][c][d] = min(p[i][t[i]], q[i][t[i]][t[i]]) + 5;
                if (c != t[i]) {
                    q[i + 1][c][d] = min(q[i + 1][c][d], min(p[i][c], q[i][c][t[i]]) + 3);
                    if (d != t[i]) q[i + 1][c][d] = min(q[i + 1][c][d], q[i][c][d] + 1);
                }
                if (d != t[i]) q[i + 1][c][d] = min(q[i + 1][c][d], q[i][t[i]][d] + 3);
            }
        }
    }

    cout << 2 * e_cnt + p[t_cnt][4] - 2;
    return 0;
}