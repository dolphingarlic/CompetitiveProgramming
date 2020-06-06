/*
NOI.sg 2011 Paint
- We will always pay for the first cost, so jsut add them to the answer
- Sort the second cost in descending order and just simulate the answer
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[20000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, ans = 0;
    cin >> n;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        ans += x;
    }
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n, greater<int>());
    FOR(i, 0, n) ans += a[i] * i;
    cout << ans;
    return 0;
}