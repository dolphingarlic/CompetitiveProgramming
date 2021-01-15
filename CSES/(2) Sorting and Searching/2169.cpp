#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MX = 1e9;

struct Node {
    int val, l, r;
    Node *lc, *rc;

    Node(int _l = 1, int _r = MX): val(0), l(_l), r(_r), lc(nullptr), rc(nullptr) {}

    void update(int pos, int delta) {
        val += delta;
        if (l == r) return;
        int mid = (l + r) / 2;
        if (pos > mid) {
            if (!rc) rc = new Node(mid + 1, r);
            rc->update(pos, delta);
        } else {
            if (!lc) lc = new Node(l, mid);
            lc->update(pos, delta);
        }
    }

    int query(int a, int b) {
        if (l > b || r < a) return 0;
        if (l >= a && r <= b) return val;
        int ans = 0;
        if (lc) ans += lc->query(a, b);
        if (rc) ans += rc->query(a, b);
        return ans;
    }
};

pair<pair<int, int>, int> rng[200001];
int inner[200001], outer[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> rng[i].first.first >> rng[i].first.second;
        rng[i].second = i;
    }
    sort(rng, rng + n, [](pair<pair<int, int>, int> A, pair<pair<int, int>, int> B) {
        if (A.first.first == B.first.first) return A.first.second > B.first.second;
        return A.first.first < B.first.first;
    });
    Node *left_root = new Node(), *right_root = new Node();
    for (int i = 0; i < n; i++) right_root->update(rng[i].first.second, 1);
    for (int i = 0; i < n; i++) {
        right_root->update(rng[i].first.second, -1);
        inner[rng[i].second] = right_root->query(1, rng[i].first.second);
        outer[rng[i].second] = left_root->query(rng[i].first.second, MX);
        left_root->update(rng[i].first.second, 1);
    }
    for (int i = 0; i < n; i++) cout << inner[i] << ' ';
    cout << '\n';
    for (int i = 0; i < n; i++) cout << outer[i] << ' ';
    return 0;
}