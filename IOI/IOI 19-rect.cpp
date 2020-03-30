/*
IOI 2019 Rectangles
- For each row and column, we find all pairs of cells that can be on the border
    - Notice that there are at most 2N of these pairs in each row/column
    - Additionally, if there is a border pair (X, Y) where H[X] < H[Y] and X < Y,
      then there is no Z > Y such that (X, Z) is a border pair and H[X] < H[Z]
    - This means we can just use a monotone stack to find the first cells to the left
      and right that is not less than each element
        - These two cells both form a border pair with the current cell
- Next, for each border pair, compute how far up/down/left/right the border containing
  that pair stretches
    - Now we can check in O(1) whether a rectangle is valid
    - Consult the implementation for more details
- Lastly, we want to test each potential rectangle
    - There are 6 potential rectangles for each cell
    - Just brute force and check them all
    - If a rectangle is valid, add it to a set and return the size of the set at the end
- Complexity: O(N^2)
*/

#include "rect.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int gl[3000][3000], gr[3000][3000], gu[3000][3000], gd[3000][3000];
int lu[3000][3000], ru[3000][3000], ul[3000][3000], dl[3000][3000];
unordered_set<ll> rects;

void check(int x1, int x2, int y1, int y2) {
    if (x2 < x1 || y2 < y1) return;
    if (!((gl[x2][y2 + 1] + 1 == y1 && lu[x2][y2 + 1] <= x1) || (gr[x2][y1 - 1] - 1 == y2 && ru[x2][y1 - 1] <= x1))) return;
    if (!((gu[x2 + 1][y2] + 1 == x1 && ul[x2 + 1][y2] <= y1) || (gd[x1 - 1][y2] - 1 == x2 && dl[x1 - 1][y2] <= y1))) return;
    rects.insert(((x1 * 3000ll + x2) * 3000ll + y1) * 3000ll + y2);
}

ll count_rectangles(vector<vector<int>> a) {
    int n = a.size(), m = a[0].size();

    for (int i = 0; i < n; i++) {
        vector<int> stck;
        for (int j = 0; j < m; j++) {
            while (stck.size() && a[i][stck.back()] < a[i][j]) stck.pop_back();
            if (stck.size()) gl[i][j] = stck.back();
            else gl[i][j] = -1;
            stck.push_back(j);
        }
        stck.clear();
        for (int j = m - 1; ~j; j--) {
            while (stck.size() && a[i][stck.back()] < a[i][j]) stck.pop_back();
            if (stck.size()) gr[i][j] = stck.back();
            else gr[i][j] = -1;
            stck.push_back(j);
        }
    }

    for (int i = 0; i < m; i++) {
        vector<int> stck;
        for (int j = 0; j < n; j++) {
            while (stck.size() && a[stck.back()][i] < a[j][i]) stck.pop_back();
            if (stck.size()) gu[j][i] = stck.back();
            else gu[j][i] = -1;
            stck.push_back(j);
        }
        stck.clear();
        for (int j = n - 1; ~j; j--) {
            while (stck.size() && a[stck.back()][i] < a[j][i]) stck.pop_back();
            if (stck.size()) gd[j][i] = stck.back();
            else gd[j][i] = -1;
            stck.push_back(j);
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (~gl[i][j]) {
                if (i && gl[i - 1][j] == gl[i][j]) lu[i][j] = lu[i - 1][j];
                else if (i && gr[i - 1][gl[i][j]] == j) lu[i][j] = ru[i - 1][gl[i][j]];
                else lu[i][j] = i;
            }
            if (~gr[i][j]) {
                if (i && gr[i - 1][j] == gr[i][j]) ru[i][j] = ru[i - 1][j];
                else if (i && gl[i - 1][gr[i][j]] == j) ru[i][j] = lu[i - 1][gr[i][j]];
                else ru[i][j] = i;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (~gu[j][i]) {
                if (i && gu[j][i - 1] == gu[j][i]) ul[j][i] = ul[j][i - 1];
                else if (i && gd[gu[j][i]][i - 1] == j) ul[j][i] = dl[gu[j][i]][i - 1];
                else ul[j][i] = i;
            }
            if (~gd[j][i]) {
                if (i && gd[j][i - 1] == gd[j][i]) dl[j][i] = dl[j][i - 1];
                else if (i && gu[gd[j][i]][i - 1] == j) dl[j][i] = ul[gd[j][i]][i - 1];
                else dl[j][i] = i;
            }
        }
    }

    for (int i = 1; i < n - 1; i++) for (int j = 1; j < m - 1; j++) {
        if (~gl[i][j + 1] && ~gu[i + 1][j]) check(gu[i + 1][j] + 1, i, gl[i][j + 1] + 1, j);
        if (~gl[i][j + 1] && ~gd[i - 1][j]) check(i, gd[i - 1][j] - 1, gl[i][j + 1] + 1, j);
        if (~gr[i][j - 1] && ~gu[i + 1][j]) check(gu[i + 1][j] + 1, i, j, gr[i][j - 1] - 1);
        if (~gr[i][j - 1] && ~gd[i - 1][j]) check(i, gd[i - 1][j] - 1, j, gr[i][j - 1] - 1);

        if (~gr[i][j - 1] && ~gd[i - 1][gr[i][j - 1] - 1])
            check(i, gd[i - 1][gr[i][j - 1] - 1] - 1, j, gr[i][j - 1] - 1);
        if (~gd[i - 1][j] && ~gr[gd[i - 1][j] - 1][j - 1])
            check(i, gd[i - 1][j] - 1, j, gr[gd[i - 1][j] - 1][j - 1] - 1);
    }

    return rects.size();
}
