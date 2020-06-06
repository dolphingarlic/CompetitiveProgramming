/*
NOI.sg 2009 Xmas
- Just do it
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int ans[20001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        int k;
        cin >> k;
        ans[k] = i;
    }
    FOR(i, 1, n + 1) cout << ans[i] << '\n';
    return 0;
}