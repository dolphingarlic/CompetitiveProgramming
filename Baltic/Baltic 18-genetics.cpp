#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

bitset<4100> is[26][4100];
bool not_villain[4100];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    k = m - k;
    FOR(i, 0, n) {
        cin.ignore();
        FOR(j, 0, m) is[cin.get() - 'A'][i][j] = 1;
        FOR(j, 0, i) {
            int cnt = ((is[0][i] & is[0][j]) | (is[2][i] & is[2][j]) | (is[6][i] & is[6][j]) | (is[19][i] & is[19][j])).count();
            not_villain[i] |= (cnt != k);
            not_villain[j] |= (cnt != k);
        }
    }

    FOR(i, 0, n) if (!not_villain[i]) cout << i + 1 << '\n';
    return 0;
}