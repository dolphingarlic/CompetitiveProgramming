/*
Baltic 2011 Growing Trees
- First, sort the trees
- Handling type C queries is easy - just binary search for boundaries
- For type F queries...
    - First, find the smallest tree with height >= H. Let this tree be L
        - If N - L < A or L doesn't exist, update the trees
    - Let mx be the current height of tree L + C - 1
    - Find the tallest tree with height < mx. Let this tree be R
    - Increase all heights of trees [L, R] by 1
    - Find the tallest tree with height > mx. Let this tree be S
    - Increase all heights of trees [S - A - L + R, S - 1]
    - Notice how the heights will still be nondecreasing after this
- To efficiently handle range updates and point queries, we use a BIT
- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int n, q, bit[100001], a[100001];

void update(int l, int r, int val) {
    for (; l <= n; l += (l & (-l))) bit[l] += val;
    for (r++; r <= n; r += (r & (-r))) bit[r] -= val;
}
int query(int pos) {
    int ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    FOR(i, 1, n + 1) cin >> a[i];
    sort(a + 1, a + n + 1);
    FOR(i, 1, n + 1) update(i, i, a[i]);

    while (q--) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        if (c == 'F') {
            int l1 = 1, r1 = n;
            while (l1 != r1) {
                int mid = (l1 + r1) / 2;
                if (query(mid) < b) l1 = mid + 1;
                else r1 = mid;
            }
            if (query(l1) < b) continue;
            if (n - l1 < a) {
                update(l1, n, 1);
                continue;
            }

            int l2 = l1 - 1, r2 = l1 + a - 1, mx = query(r2);
            while (l2 != r2) {
                int mid = (l2 + r2 + 1) / 2;
                if (query(mid) == mx) r2 = mid - 1;
                else l2 = mid;
            }
            int l3 = 1, r3 = n;
            while (l3 != r3) {
                int mid = (l3 + r3 + 1) / 2;
                if (query(mid) > mx) r3 = mid - 1;
                else l3 = mid;
            }

            update(l1, l2, 1);
            a -= l2 - l1 + 1;
            update(l3 - a + 1, l3, 1);
        } else {
            if (a > query(n) || b < query(1)) {
                cout << "0\n";
                continue;
            }

            int l1 = 1, r1 = n, l2 = 1, r2 = n;
            while (l1 != r1) {
                int mid = (l1 + r1) / 2;
                if (query(mid) < a) l1 = mid + 1;
                else r1 = mid;
            }
            while (l2 != r2) {
                int mid = (l2 + r2 + 1) / 2;
                if (query(mid) > b) r2 = mid - 1;
                else l2 = mid;
            }

            cout << l2 - l1 + 1 << '\n';
        }
    }
    return 0;
}