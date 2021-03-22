/*
CEOI 2014 Cake
- Let's assume WLOG that b < a in each query
- Also, let d[0] = d[N + 1] = INF
- The answer for a query is simply
    min(c : max(d[a : c]) >= max(d[b : a])) - b
- We can use a segtree to store range minimums and walk down it to get c
- To handle an update efficiently, decrement the "rank" of the e - 1 tastiest
  pieces and set the 
    - The "ranks" may become negative, but we only care about relative order
- We can use a std::set to store the order of the cakes
- Complexity: O(max(e) * Q log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int d[250001], segtree[2][1000001];

void update(int *seg, int pos, int val, int node, int l, int r) {
    if (l == r) seg[node] = val;
    else {
        int mid = (l + r) / 2;
        if (pos > mid) update(seg, pos, val, node * 2 + 1, mid + 1, r);
        else update(seg, pos, val, node * 2, l, mid);
        seg[node] = max(seg[node * 2], seg[node * 2 + 1]);
    }
}

int range_max(int *seg, int a, int b, int node, int l, int r) {
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return seg[node];
    int mid = (l + r) / 2;
    return max(range_max(seg, a, b, node * 2, l, mid), range_max(seg, a, b, node * 2 + 1, mid + 1, r));
}

int walk(int *seg, int threshold, int node, int l, int r) {
    if (threshold > seg[node]) return r;
    if (l == r) return l - (seg[node] > threshold);
    int mid = (l + r) / 2;
    if (seg[node * 2] >= threshold) return walk(seg, threshold, node * 2, l, mid);
    return walk(seg, threshold, node * 2 + 1, mid + 1, r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, a;
    cin >> n >> a;
    vector<int> top_ten;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
        top_ten.push_back(i);
    }
    sort(top_ten.begin(), top_ten.end(), [](int A, int B) { return d[A] > d[B]; });
    while (top_ten.size() > 10) top_ten.pop_back();

    for (int i = a + 1; i <= n; i++) update(segtree[0], i - a, d[i], 1, 1, n - a);
    for (int i = a - 1; i; i--) update(segtree[1], a - i, d[i], 1, 1, a - 1);

    int q;
    cin >> q;
    while (q--) {
        char c;
        cin >> c;
        if (c == 'F') {
            int b;
            cin >> b;
            if (b == a) cout << "0\n";
            else if (b > a) {
                int mx = range_max(segtree[0], 1, b - a, 1, 1, n - a);
                cout << walk(segtree[1], mx, 1, 1, a - 1) + b - a << '\n';
            } else {
                int mx = range_max(segtree[1], 1, a - b, 1, 1, a - 1);
                cout << walk(segtree[0], mx, 1, 1, n - a) + a - b << '\n';
            }
        } else {
            int i, e;
            cin >> i >> e;

            auto it = find(top_ten.begin(), top_ten.end(), i);
            if (it != top_ten.end()) top_ten.erase(it);
            
            for (int i = 0; i < e - 1; i++) {
                d[top_ten[i]]++;
                if (top_ten[i] > a)
                    update(segtree[0], top_ten[i] - a, d[top_ten[i]], 1, 1, n - a);
                else if (top_ten[i] < a)
                    update(segtree[1], a - top_ten[i], d[top_ten[i]], 1, 1, a - 1);
            }

            d[i] = d[top_ten[e - 1]] + 1;
            if (i > a) update(segtree[0], i - a, d[i], 1, 1, n - a);
            else if (i < a) update(segtree[1], a - i, d[i], 1, 1, a - 1);

            top_ten.insert(top_ten.begin() + e - 1, i);
            if (top_ten.size() > 10) top_ten.pop_back();
        }
    }
    return 0;
}
