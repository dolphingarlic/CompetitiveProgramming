#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    char curr = '_', x;
    int mx = 0, cnt = 0;
    while (cin >> x) {
        if (x == curr) cnt++;
        else {
            mx = max(mx, cnt);
            cnt = 1;
            curr = x;
        }
    }
    mx = max(mx, cnt);
    cout << mx << '\n';
    return 0;
}