#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int H[11]{0, 6, 100, 100, 100, 100, 11, 20, 20, 11, 200},
          W[11]{0, 10, 100, 100, 100, 100, 11, 20, 20, 21, 200},
          best[11]{0, 20, 3002, 2506, 2000, 3000, 54, 33, 93, 104, 2700};
const bool needed[11]{0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 1};
const string inp[11]{"", "field1.txt", "field2.txt", "field3.txt", "field4.txt", "field5.txt", "field6.txt", "field7.txt", "field8.txt", "field9.txt", "fieldA.txt"},
             oup[11]{"", "maze1.txt", "maze2.txt", "maze3.txt", "maze4.txt", "maze5.txt", "maze6.txt", "maze7.txt", "maze8.txt", "maze9.txt", "mazeA.txt"};
const int dx[4]{-1, 0, 1, 0}, dy[4]{0, 1, 0, -1};
int f, cnt;

char field[200][200];

bool good(int x, int y) {
    return (x && y && x < H[f] - 1 && y < W[f] - 1 &&
            field[x][y] == '#' &&
            (field[x - 1][y] == '.') + (field[x + 1][y] == '.') + (field[x][y - 1] == '.') + (field[x][y + 1] == '.') == 1);
}

bool dfs(int x, int y, int dir) {
    field[x][y] = '.';
    cnt++;
    // Try to go straight if possible
    if (good(x + dx[dir], y + dy[dir])) {
        if (dfs(x + dx[dir], y + dy[dir], dir)) return true;
        // else if (cnt > best[f] / 4) {
        //     field[x][y] = '#';
        //     cnt--;
        //     return false;
        // }
    }
    // Otherwise, try to turn
    dir = (dir + 1) % 4;
    if (good(x + dx[dir], y + dy[dir])) {
        if (dfs(x + dx[dir], y + dy[dir], dir)) return true;
        // else if (cnt > best[f] / 4) {
        //     field[x][y] = '#';
        //     cnt--;
        //     return false;
        // }
    }
    dir = (dir + 2) % 4;
    if (good(x + dx[dir], y + dy[dir])) {
        if (dfs(x + dx[dir], y + dy[dir], dir)) return true;
        // else if (cnt > best[f] / 4) {
        //     field[x][y] = '#';
        //     cnt--;
        //     return false;
        // }
    }
    // If cnt > best[f] break
    if (cnt > best[f]) return true;
    // Otherwise, backtrack
    field[x][y] = '#';
    cnt--;
    return false;
}

int main() {
    for (f = 4; f <= 5; f++) {
        if (!needed[f]) continue;
        ifstream cin(inp[f]);
        for (int i = 0; i < H[f]; i++) for (int j = 0; j < W[f]; j++) cin >> field[i][j];
        cin.close();
        cnt = 0;
        dfs(1, 0, 1);
        cerr << f << ' ' << cnt << '\n';
        if (cnt > best[f]) {
            ofstream cout(oup[f]);
            for (int i = 0; i < H[f]; i++) {
                for (int j = 0; j < W[f]; j++) cout << field[i][j];
                cout << '\n';
            }
            cout.close();
        }
    }
    return 0;
}