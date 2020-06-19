/*
IOI 2005 Mountains
- Just use a dynamic segtree with lazy propagation
- Alternatively, read all the input, compress it, and then use a normal segtree
- Complexity: O(Q log N)
*/

#include <bits/stdc++.h>
using namespace std;

int n, a, b, d;
char op;
struct Node {
    int sum, greater, l, r, lazy;
    Node *l_child, *r_child;

    Node(int L = 1, int R = n) {
        sum = 0, greater = 0, l = L, r = R, lazy = INT_MIN;
    }

    void push_lazy() {
        if (!l_child && r > l) {
            l_child = new Node(l, (l + r) / 2);
            r_child = new Node((l + r) / 2 + 1, r);
        }

        if (lazy != INT_MIN) {
            if (r > l) l_child->lazy = r_child->lazy = lazy;
            sum = greater = (r - l + 1) * lazy;
            lazy = INT_MIN;
        }
    }

    int query(int h) {
        push_lazy();

        if (l == r) {
            if (greater > h) return l - 1;
            return l;
        }

        l_child->push_lazy();

        if (l_child->greater > h) return l_child->query(h);
        return r_child->query(h - l_child->sum);
    }

    void update(int a, int b, int d) {
        push_lazy();

        if (a > r || b < l) return;

        if (a <= l && b >= r) {
            lazy = d;
            push_lazy();
            return;
        }

        l_child->update(a, b, d);
        r_child->update(a, b, d);

        sum = l_child->sum + r_child->sum;
        greater = max(l_child->greater, l_child->sum + r_child->greater);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    Node* segtree = new Node();

    while (cin >> op && op != 'E') {
        if (op == 'Q') {
            cin >> a;
            cout << segtree->query(a) << '\n';
        } else {
            cin >> a >> b >> d;
            segtree->update(a, b, d);
        }
    }
    return 0;
}