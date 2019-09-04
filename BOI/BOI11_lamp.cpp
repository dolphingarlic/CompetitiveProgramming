#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

char a[500][500];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    if ((n + m) & 1) return cout << "NO SOLUTION", 0;

    FOR(i, 0, n) FOR(j, 0, m) cin >> a[i][j];
    return 0;
}