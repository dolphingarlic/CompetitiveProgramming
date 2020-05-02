/*
JOI 2013 Bubblesort
- Plot the points (i, A[i]) on the plane
- If we swap i and j (i < j and A[i] > A[j]), then the number of inversions saved
  = (No. of points strictly inside the rectangle (i, A[i], j, A[j])) + (No. of points in or on the rectangle (i, A[i], j, A[j])) - 1
- Notice how if we swap i with some j > i and there is some k > i such that A[i] > A[k], then k is never in the optimal swap
    - This means we can just consider a set of i with strictly increasing A[i] as candidates
- Since this set is strictly increasing, opt[i] >= opt[i - 1] and so we can do D&C dp
- To find the number of points in a rectangle, we use a BIT
- Complexity: O(N log^2 N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll ans = 0, bit[100001];
int n, a[100001], b[100001];
vector<int> cand;

void update(int pos, ll val) {
    for (; pos <= n; pos += pos & (-pos)) bit[pos] += val;
}

ll query(int x, int y) {
    ll ans = 0;
    for (; y; y -= y & (-y)) ans += bit[y];
    for (x--; x; x -= x & (-x)) ans -= bit[x];
    return ans;
}

void divide_conquer(int l = 0, int r = cand.size() - 1, int l_opt = 0, int r_opt = n - 1) {
    int mid = (l + r) / 2, opt = -1;
    ll best_delta = 1;
    FOR(i, max(l_opt, cand[mid]), r_opt + 1) {
        update(a[i], 1);
        int inv = 1 - query(a[i] + 1, a[cand[mid]] - 1) - query(a[i], a[cand[mid]]);
        if (inv <= best_delta) best_delta = inv, opt = i;
    }
    ans = min(ans, best_delta);

    if (mid != r) {
        FOR(i, cand[mid], cand[(mid + r + 1) / 2]) update(a[i], -1);
        FOR(i, max(opt, cand[(mid + r + 1) / 2]), r_opt + 1) update(a[i], -1);
        divide_conquer(mid + 1, r, opt, r_opt);
        FOR(i, cand[mid], cand[(mid + r + 1) / 2]) update(a[i], 1);
        FOR(i, max(opt, cand[(mid + r + 1) / 2]), r_opt + 1) update(a[i], 1);
    }

    if (mid != l) {
        FOR(i, cand[(mid + l - 1) / 2], min(l_opt, cand[mid])) update(a[i], 1);
        FOR(i, max(l_opt, cand[mid]), r_opt + 1) update(a[i], -1);
        divide_conquer(l, mid - 1, l_opt, opt);
        FOR(i, cand[(mid + l - 1) / 2], min(l_opt, cand[mid])) update(a[i], -1);
        FOR(i, max(l_opt, cand[mid]), r_opt + 1) update(a[i], 1);
    }

    FOR(i, max(l_opt, cand[mid]), r_opt + 1) update(a[i], -1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    bool sorted = true, distinct = true;
    FOR(i, 0, n) {
        cin >> a[i];
        b[i] = a[i];
        if (i) sorted &= (a[i] >= a[i - 1]), distinct &= (a[i] != a[i - 1]);
    }
    if (sorted) return cout << distinct << '\n', 0;

    sort(b, b + n);
    FOR(i, 0, n) {
        a[i] = lower_bound(b, b + n, a[i]) - b + 1;
        if (!i || a[i] > a[cand.back()]) cand.push_back(i);
    }

    divide_conquer();
    for (int i = n - 1; ~i; i--) {
        update(a[i], 1);
        ans += query(1, a[i] - 1);
    }
    cout << ans << '\n';
    return 0;
}