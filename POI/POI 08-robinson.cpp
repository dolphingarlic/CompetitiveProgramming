/*
POI 2008 Robinson
- Instead of focusing on which positions the boat can be in, consider the
  positions each rock obstructs
    - Represent the boat by a single point
    - Notice how the obstructed points are basically just the shape of the boat
      but rotated 180 degrees
- 
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
using namespace std;

vector<short> w;
short n, m, obstruct[6000][6000], visited[6000][6000];
bool low_seas[6000][6000];
char grid[6000][6000];
vector<pair<short, short>> d = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

inline bool vertical() {
    w.clear();
    for (short j = n; j < 2 * n; j++) {
        short curr = 0;
        for (short i = n; i < 2 * n; i++) if (grid[i][j] == 'r') curr++;
        if (curr) w.push_back(curr);
    }
    m = w.size();
    for (short i = 0; i < m / 2; i++) if (w[i] != w[m - 1 - i]) return false;
    return true;
}

inline bool inside(short x, short y) { return ~x && ~y && x != 3 * n && y != 3 * n; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (short i = n; i < 2 * n; i++) for (short j = n; j < 2 * n; j++)
        cin >> grid[i][j];
    if (vertical()) {
        for (short i = n; i < 2 * n; i++) for (short j = n; j < i; j++)
            swap(grid[i][j], grid[j][i]);
    }
    vertical();
    
    short mid = max_element(w.begin(), w.end()) - w.begin();
    
    for (short i = 0; i < 3 * n; i++) {
        deque<short> q, r;
        for (short j = 0; j < 3 * n; j++) {
            while (q.size() && q[0] - j + mid == -1) q.pop_front();
            while (r.size() && r[0] - j + mid == -1) r.pop_front();

            if (j + m - mid - 1 < 3 * n && grid[i][j + m - mid - 1] == 'X')
                q.push_back(j + m - mid - 1);
            if (i < 2 * n && i > n && j + m - mid - 1 < 2 * n && j + m - mid - 1 >= n)
                r.push_back(j + m - mid - 1);

            while (q.size() > 1 && w[q[0] - j + mid] < w[q[1] - j + mid])
                q.pop_front();
            while (r.size() > 1 && w[r[0] - j + mid] < w[r[1] - j + mid])
                r.pop_front();
            
            if (q.size()) {
                obstruct[i - w[q[0] - j + mid] / 2][j]++;
                obstruct[i + w[q[0] - j + mid] / 2 + 1][j]--;
            }
            if (r.size()) {
                low_seas[i - w[r[0] - j + mid] / 2][j] = true;
                low_seas[i + w[r[0] - j + mid] / 2][j] = true;
            }
        }
    }
    
    short ix, iy;
    for (short j = n; j < 2 * n; j++) {
        short curr = 0, lst;
        for (short i = n; i < 2 * n; i++) if (grid[i][j] == 'r') curr++, lst = i;
        if (curr == w[mid]) iy = j, ix = lst - w[mid] / 2;
    }
    
    for (short j = 0; j < 3 * n; j++) for (short i = 1; i < 3 * n; i++)
        obstruct[i][j] += obstruct[i - 1][j];

    queue<pair<short, short>> q;
    q.push({ix, iy});
    visited[ix][iy] = 1;
    while (q.size()) {
        short x = q.front().first, y = q.front().second;
        q.pop();
        if (!low_seas[x][y]) return cout << visited[x][y] - 1, 0;
        for (pair<short, short> i : d) {
            if (inside(x + i.first, y + i.second) && !visited[x + i.first][y + i.second] && !obstruct[x + i.first][y + i.second]) {
                visited[x + i.first][y + i.second] = visited[x][y] + 1;
                q.push({x + i.first, y + i.second});
            }
        }
    }
    cout << "NIE";
    return 0;
}