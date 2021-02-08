/*
IOI 2008 Fish
- Firstly, notice that we only care when the longest fish of some type eats other fish
    - Let the length of this fish for type i be MX[i]
    - Furthermore, assume that the types are sorted in increasing order of MX[i]
- Sort the fish and iterate
- Let's keep track of an array A of the number of fish of each type that a fish can eat
- Case 1: The longest fish of type i eats only fish of type j where i > j
    - The number of combinations this contributes is
        prod(A[j] + 1 : i >= j)
- Case 2: In addition to case 1, the longest fish of type i also eats fish of type j
          where the smallest fish of type i that the longest fish of type i can't eat
          also can't be eaten by the longest fish of type j, and the longest fish of
          type i eats all the other fish of type i that it can eat
    - We need this case because it's not covered by case 1 (think about it)
        - This makes sense to me but it's like 11pm and I'm tired so what do I know
    - Let the largest such j be l
        - We can find l using binary search
    - The number of combinations this contributes is
        prod(A[j] + 1 : i > j) * (prod(A[j] + 1 : i < j <= l) - 1)
- We can handle range products with updates efficiently using a segment tree
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

int n, k, m, segtree[2000001];
array<int, 3> f[500001];
pair<int, int> mx[500001];
int nxt[500001], ord[500001], idx[500001];

void increment(int pos, int node = 1, int l = 1, int r = k) {
    if (l == r) segtree[node] = (segtree[node] + 1) % m;
    else {
        int mid = (l + r) / 2;
        if (pos > mid) increment(pos, node * 2 + 1, mid + 1, r);
        else increment(pos, node * 2, l, mid);
        segtree[node] = (segtree[node * 2] * segtree[node * 2 + 1]) % m;
    }
}

int query(int a, int b, int node = 1, int l = 1, int r = k) {
    if (l > b || r < a) return 1;
    if (l >= a && r <= b) return segtree[node];
    int mid = (l + r) / 2;
    return (query(a, b, node * 2, l, mid) * query(a, b, node * 2 + 1, mid + 1, r)) % m;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k >> m;
    fill(segtree + 1, segtree + 4 * k + 1, 1);
    for (int i = 1; i <= n; i++) {
        int l, t;
        cin >> l >> t;
        mx[t] = max(mx[t], {l, i});
        nxt[t] = max(nxt[t], l);
        f[i] = {l, t, i};
    }
    for (int i = 1; i <= n; i++)
        if (mx[f[i][1]].first < f[i][0] * 2)
            nxt[f[i][1]] = min(nxt[f[i][1]], f[i][0]);

    sort(f + 1, f + n + 1);
    iota(ord + 1, ord + k + 1, 1);
    sort(ord + 1, ord + k + 1, [](int A, int B) { return mx[A] < mx[B]; });
    for (int i = 1; i <= k; i++) idx[ord[i]] = i;

    int ans = 0;
    for (int i = 1, j = 1; i <= n; i++) {
        while (f[i][0] >= get<0>(f[j]) * 2) increment(idx[get<1>(f[j++])]);
        if (f[i][2] == mx[f[i][1]].second) {
            ans = (ans + query(1, idx[f[i][1]])) % m;
            int l = idx[f[i][1]], r = k;
            while (l != r) {
                int mid = (l + r + 1) / 2;
                if (mx[ord[mid]].first < nxt[f[i][1]] * 2) l = mid;
                else r = mid - 1;
            }
            ans = (ans + query(1, idx[f[i][1]] - 1) * (query(idx[f[i][1]] + 1, l) + m - 1)) % m;
        }
    }
    cout << ans;
    return 0;
}
