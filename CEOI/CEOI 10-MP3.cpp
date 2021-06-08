/*
CEOI 2010 MP3
- Imagine we have a bitset for each potential T
- Each operation involves shifting a suffix of those bitsets left or right
- We can basically keep track of the minimum and maximum shifted values,
  and keep a "delta" value that stores how far left/right we've shifted
- To handle this, we use a lazy segtree with range add/subtract/min/max
    - Merging two nodes can be quite tricky; see code for details
- For simplicity, we also coordinate compress the times between
  successive button presses
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, vmax, v2, c[200001];

struct Node {
    int curr, mn, mx;

    Node operator+(Node B) {
        if (mx + curr <= B.mn) return {B.mn + B.curr - vmax, vmax, vmax};
        if (mn + curr >= B.mx) return {B.mx + B.curr - vmax, vmax, vmax};
        return {curr + B.curr, max(mn, B.mn - curr), min(mx, B.mx - curr)};
    }
} segtree[800001], lazy[800001];

char op[200001];
vector<int> comp;

void push_lazy(int node, int l, int r) {
    segtree[node] = segtree[node] + lazy[node];
    if (l != r) {
        lazy[node * 2] = lazy[node * 2] + lazy[node];
        lazy[node * 2 + 1] = lazy[node * 2 + 1] + lazy[node];
    }
    lazy[node] = {0, 0, vmax};
}

void update(int a, int b, int val, int node = 1, int l = 0,
            int r = comp.size() - 1) {
    push_lazy(node, l, r);
    if (l > b || r < a) return;
    if (l >= a && r <= b) {
        lazy[node] = {val, max(0, -val), vmax - max(0, val)};
        push_lazy(node, l, r);
    } else {
        int mid = (l + r) / 2;
        update(a, b, val, node * 2, l, mid);
        update(a, b, val, node * 2 + 1, mid + 1, r);
    }
}

Node query(int pos, int node = 1, int l = 0, int r = comp.size() - 1) {
    push_lazy(node, l, r);
    if (l == r) return segtree[node];
    int mid = (l + r) / 2;
    if (pos > mid) return query(pos, node * 2 + 1, mid + 1, r);
    return query(pos, node * 2, l, mid);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> vmax >> v2;
    for (int i = 0; i < n; i++) {
        cin >> op[i] >> c[i];
        if (i) comp.push_back(c[i] - c[i - 1]);
    }
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    Node base = {0, 0, vmax};
    fill_n(segtree + 1, 4 * n, base);
    fill_n(lazy + 1, 4 * n, base);

    for (int i = 1; i < n; i++) {
        int pos = lower_bound(comp.begin(), comp.end(), c[i] - c[i - 1]) -
                  comp.begin();
        int val = (op[i] == '+' ? 1 : -1);
        update(pos, comp.size() - 1, val);
    }
    for (int i = comp.size() - 1; ~i; i--) {
        Node res = query(i);
        int l = res.mn + res.curr, r = res.mx + res.curr;
        if (l <= v2 && v2 <= r) {
            if (i == comp.size() - 1)
                cout << "infinity";
            else {
                cout << comp[i + 1] - 1 << ' ';
                if (v2 == r)
                    cout << vmax;
                else
                    cout << v2 - res.curr;
            }
            return 0;
        }
    }
    cout << comp[0] - 1 << ' ' << v2;
    return 0;
}