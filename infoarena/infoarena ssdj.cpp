/*
infoarena SSDJ
- First, flip the grid vertically because that makes indexing easier
- For each letter c, count the number of rectangles where it's one of the "bad" corners
- For each (i, j), find the first letters above and to the left of (i, j) that are >=c
    - Let these be vert[i][j] and horiz[i][j]
- Next, we want to know how far the rectangle with bottom right corner (i, j) can stretch
    - To do this, we use a monotone stack (kinda like IOI 2019 Rect)
- Then we can check each rectangle with bottom right corner (i, j) in O(1)
- Complexity: O(26N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int n;
int v[1001][1001], h[1001][1001];
int v_stck[1001], h_stck[1001], v_cnt, h_cnt;
int v_ext[1001][1001], h_ext[1001][1001];
char a[1001][1001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("ssdj.in");
    ofstream cout("ssdj.out");

    cin >> n;
    n++;
    FOR(i, 1, n) FOR(j, 1, n) cin >> a[n - i][j];

    int ans = 0;
    for (char c = 'a'; c <= 'z'; c++) {
        FOR(i, 1, n) {
            v_cnt = h_cnt = 0;
            FOR(j, 1, n) {
                if (a[i][j] >= c) v[i][j] = i;
                else v[i][j] = v[i - 1][j];
                while (v_cnt && v[i][v_stck[v_cnt]] < v[i][j]) v_cnt--;
                if (v_cnt) v_ext[i][j] = v_stck[v_cnt];
                else v_ext[i][j] = 0;
                v_stck[++v_cnt] = j;

                if (a[j][i] >= c) h[j][i] = i;
                else h[j][i] = h[j][i - 1];
                while (h_cnt && h[h_stck[h_cnt]][i] < h[j][i]) h_cnt--;
                if (h_cnt) h_ext[j][i] = h_stck[h_cnt];
                else h_ext[j][i] = 0;
                h_stck[++h_cnt] = j;
            }
        }

        FOR(i, 1, n) FOR(j, 1, n) {
            if (a[v[i][j]][j] == c || a[i][h[i][j]] == c) {
                if (v[i][j] && h[i][j]) {
                    if (v_ext[i][j] == h[i][j] && h_ext[i][j] == v[i][j]) {
                        if (a[v[i][j]][h[i][j]] < c) ans++;
                    }
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}