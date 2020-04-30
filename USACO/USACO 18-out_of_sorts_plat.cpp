/*
USACO 2018 Out Of Sorts - Platinum
- Notice how instead of recursing, we can just remove pivot points and iterate
- This suggests that we should count how many passes until an element is removed for each element
- An element becomes a pivot point only when all elements smaller than it lie on the left and all elements
  greater than it lie on the right
    - The number of passes it takes for this to happen is equal to max_index(Elements < i) + 1 - i
- So sort the elements and find max_index for each i
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, a[100001], idx[100001], part_points[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("sort.in");
    ofstream cout("sort.out");

    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    iota(idx, idx + n, 0);
    sort(idx, idx + n, [](int X, int Y) {
        if (a[X] == a[Y]) return X < Y;
        return a[X] < a[Y];
    });

    int mx = 0;
    FOR(i, 1, n) {
        mx = max(mx, idx[i - 1]);
        part_points[i] = mx + 1 - i;
    }

    ll ans = 0;
    FOR(i, 0, n) {
        int contrib = 0;
        if (i) contrib = max(contrib, part_points[i]);
        if (i != n - 1) contrib = max(contrib, part_points[i + 1]);
        if (!contrib && n > 1) contrib++;
        ans += contrib;
    }
    cout << ans;
    return 0;
}