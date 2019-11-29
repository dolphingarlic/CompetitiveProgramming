#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, p, cnt = 0;
    cin >> n >> m >> p;
    FOR(i, 1, n) {
        int x;
        cin >> x;
        if (p - x >= m) cnt++;
        p = x;
    }
    cout << cnt;
    return 0;
}