#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int profit[101];
char grid[101][101];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, hi = 0, lo = 0, curr = 0;
    string s;
    cin >> n >> s;
    for (char c : s) {
        if (c == '+') hi = max(hi, ++curr);
        else if (c == '-') lo = min(lo, --curr);
    }
    int h = hi - lo + 1;
    curr = -lo;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < h; j++) grid[j][i] = '.';
        if (s[i] == '+') grid[curr++][i] = '/';
        else if (s[i] == '-') grid[--curr][i] = '\\';
        else grid[curr][i] = '_';
    }
    for (int i = h - 1; ~i; i--) {
        bool good = false;
        for (int j = 0; j < n; j++) good |= grid[i][j] != '.';
        if (!good) continue;
        for (int j = 0; j < n; j++) cout << grid[i][j];
        cout << '\n';
    }
    return 0;
}