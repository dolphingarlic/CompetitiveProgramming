#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int getR(int RGB) { return (RGB >> 16) & 0xFF; }

int getG(int RGB) { return (RGB >> 8) & 0xFF; }

int getB(int RGB) { return RGB & 0xFF; }

int getSum(int RGB) { return getR(RGB) + getB(RGB) + getG(RGB); }

int a[502][502];

double calc(int x, int y) {
    return abs((4 * getSum(a[x][y]) - getSum(a[x - 1][y]) - getSum(a[x + 1][y]) - getSum(a[x][y - 1]) - getSum(a[x][y + 1])));
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    FOR(test, 0, T) {
        int H, W;
        cin >> H >> W;
        FOR(i, 1, H + 1)
            FOR(j, 1, W + 1) cin >> a[i][j];
        FOR(i, 1, H + 1)
        a[i][W + 1] = 0x7F7F7F;
        FOR(i, 1, W + 1)
        a[H + 1][i] = 0x7F7F7F;


        double ave = 0;
        FOR(i, 1, H + 1)
        FOR(j, 1, W + 1) {
            ave += calc(i, j);
        }
        ave /= (W * H);
        if (ave < 26) cout << "4\n";
        else if (ave < 56) cout << "1\n";
        else if (ave < 160) cout << "2\n";
        else cout << "3\n";
        // cout << ave << '\n';
    }
    return 0;
}