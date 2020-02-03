/*
USACO 2018 Out of Sorts - Gold
- Firstly, since this is based on bubble sort, we should probably consider the number of inversions
- Instead of the number of inversions though, consider how many elements must pass a given "pivot"
- If we consider the sorted array and the original array and draw a line at some position, the number of
  elements that must cross that line from left to right is equal to that from right to left, so we have symmetry
- The answer is the maximum of such numbers
- We can easily find this with a Fenwick tree
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, bit[100001];
pair<int, int> a[100001];

void update(int pos) { for (; pos <= n; pos += (pos & (-pos))) bit[pos]++; }
int query(int pos) {
    int ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a + 1, a + n + 1);

    int ans = 1;
    FOR(i, 1, n + 1) {
        update(a[i].second);
        ans = max(ans, i - query(i));
    }
    cout << ans;
    return 0;
}