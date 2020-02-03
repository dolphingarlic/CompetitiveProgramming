/*
Baltic 2009 Subway Signalling
- Since the subways are periodic, we want the distance between consecutive trains in the
  same direction to be 2 * L / N
- Since trains can move simultaneously, really we want to find the minimum maximum distance
  a train moves
- Notice that trains should never cross in the optimal solution
- Because of this, if we sort the train by position, they should move LRLR... or RLRL...
    - WLOG let this be RLRL...
- If we want to move train 1 to position 0, let us consider the directed length that each other
  train would also have to move
    - Clearly, the answer is just (Max - Min) / 2
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int l, n;
    cin >> l >> n;
    FOR(i, 0, n) {
        char c;
        cin >> a[i] >> c;
    }
    sort(a, a + n);
    long double between = 2.0 * l / n;

    long double curr = 0, mx = -1e18, mn = 1e18;
    for (int i = 0; i < n; i += 2, curr += between) {
        long double dist = a[i] - curr;
        mx = max(mx, dist);
        mn = min(mn, dist);
    }
    for (int i = n - 1 - (n & 1); ~i; i -= 2, curr += between) {
        long double dist = 2 * l - a[i] - curr;
        mx = max(mx, dist);
        mn = min(mn, dist);
    }
    cout << fixed << setprecision(8) << (mx - mn) / 2;
    return 0;
}