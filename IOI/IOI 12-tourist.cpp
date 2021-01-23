#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Node {
    ll l, r, val;
    int cnt;
    Node *lc, *rc;

    Node(ll L, ll R): l(L), r(R), val(0), cnt(0), lc(nullptr), rc(nullptr) {};

    void insert(ll v) {
        val += v;
        cnt++;
        if (l == r) return;
        ll mid = (l + r) / 2;
        if (v > mid) {
            if (!rc) rc = new Node(mid + 1, r);
            rc->insert(v);
        } else {
            if (!lc) lc = new Node(l, mid);
            lc->insert(v);
        }
    }

    ll query(int k) {
        if (cnt <= k) return val;
        if (l == r) return (val / cnt) * k;
        int mid = (l + r) / 2;
        if (rc && rc->cnt >= k) return rc->query(k);
        if (!rc) return lc->query(k);
        return lc->query(k - rc->cnt) + rc->val;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    Node *root = new Node(0, INT_MAX);
    int n, k;
    cin >> n >> k;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll v;
        cin >> v;
        root->insert(v);
        ans = max(ans, root->query(k - i));
    }
    cout << ans;
    return 0;
}
