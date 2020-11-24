/*
JOI 2016 Matryoshka
- Minimum no. of increasing subsequences = LDS
- We basically want to find the LDS for points with x >= A[i] and y <= B[i]
- We can do this using a line sweep and a dynamic segtree
- Complexity: O(N log MAX_A)
*/

#include <bits/stdc++.h>
using namespace std;

struct Node {
    int l, r, val;
    Node *lc, *rc;

    Node(int L, int R): l(L), r(R), val(0), lc(nullptr), rc(nullptr) {}

    void update(int p, int v) {
        val = max(val, v);
        if (l != r) {
            int mid = (l + r) / 2;
            if (p > mid) {
                if (!rc) rc = new Node(mid + 1, r);
                rc->update(p, v);
            } else {
                if (!lc) lc = new Node(l, mid);
                lc->update(p, v);
            }
        }
    }

    int query(int a, int b) {
        if (r < a || l > b) return 0;
        if (r <= b && l >= a) return val;
        int ret = 0;
        if (lc) ret = max(ret, lc->query(a, b));
        if (rc) ret = max(ret, rc->query(a, b));
        return ret;
    }
};

pair<int, int> doll[200000];
pair<pair<int, int>, int> query[200000];
int ans[200000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> doll[i].first >> doll[i].second;
        doll[i].second = -doll[i].second;
    }
    for (int i = 0; i < q; i++) {
        cin >> query[i].first.first >> query[i].first.second;
        query[i].second = i;
    }
    sort(doll, doll + n, greater<pair<int, int>>());
    sort(query, query + q, greater<pair<pair<int, int>, int>>());

    vector<int> dp;
    Node *segtree = new Node(1, 1000000000);
    for (int i = 0, j = 0; i < q; i++) {
        while (j < n && doll[j].first >= query[i].first.first) {
            int lis = upper_bound(dp.begin(), dp.end(), -doll[j].second) - dp.begin();
            if (lis == dp.size()) dp.push_back(-doll[j].second);
            else dp[lis] = -doll[j].second;
            segtree->update(-doll[j].second, lis + 1);
            j++;
        }
        ans[query[i].second] = segtree->query(1, query[i].first.second);
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}