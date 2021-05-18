#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

char grid[61][61];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll k;
    cin >> k;
    if (k == 16)
        cout << "5 5\nXXXXd\nXXX.d\nXX..d\nX...d\nrrrr.";
    else if (k == 17)
        cout << "5 5\nXXXXd\nXXX.d\nXX..d\nXd.Xd\nrrrr.";
    else if (k == 18)
        cout << "5 5\nXXXXd\nXXX.d\nXX..d\nX..Xd\nrrrr.";
    else if (k == 19)
        cout << "5 5\nXXXXd\nXXX.d\nXX..d\nXdX.d\nrrrr.";
    else {
        int w = (k <= 19 ? 5 : 61);

        for (int i = 0; i < w; i++)
            for (int j = 0; j < w; j++) grid[i][j] = '.';
        grid[0][0] = 'r';
        for (int i = 0; i < w - 1; i++) {
            grid[i][w - 1] = 'd';
            grid[w - 1][i] = 'r';
        }
        for (int i = 1; i < w - 1; i++)
            for (int j = 0; j < w - 1 - i; j++) grid[i][j] = 'X';

        for (int i = 0; i < w - 1; i++)
            if (k & (1ll << i)) grid[0][w - 2 - i] = 'X';
        for (int i = w - 2; ~i; i--)
            if (grid[0][i] == 'X') {
                grid[0][i] = 'd';
                break;
            }

        cout << w << ' ' << w << '\n';
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < w; j++) cout << grid[i][j];
            cout << '\n';
        }
    }
    return 0;
}
