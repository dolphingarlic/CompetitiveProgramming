/*
COCI 2021 Bold
- Just do it
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

string grid[100];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) cin >> grid[i];
    for (int i = n - 2; ~i; i--) for (int j = m - 2; ~j; j--) if (grid[i][j] == '#')
        grid[i][j + 1] = grid[i + 1][j] = grid[i + 1][j + 1] = '#';
    for (int i = 0; i < n; i++) cout << grid[i] << '\n';
    return 0;
}