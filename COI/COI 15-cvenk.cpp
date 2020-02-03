/*
COI 2015 Cvenk
- Firstly, notice the Sierpinski triangle is a tree
- Since the coordinates can get very big, we'd ideally want to
  compress the tree
- Secondly, notice that a square (x, y) is white iff x + y == x ^ y
    - This means we can compress the tree based on the binary representation
      of x + y
    - Iterate i from 1 << 29 downwards. Let curr = (0, 0) initially
    - If x & (1 << i), then we add (1 << i) to curr's x coordinate
    - If y & (1 << i), then we add (1 << i) to curr's y coordinate
    - Insert the edge between the old curr and the current curr
        - We also have to take care of existing edges
- Now we have compressed our tree to O(N log N) nodes
- Finding minimum distance to all marked nodes is a standard problem
  that we can solve with DFS in O(N)
    - See https://cses.fi/problemset/task/1133
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
ll tot_dist = 0, ans = LLONG_MAX;
 
struct Node {
    ll x, y, l;
    Node *c[2];
 
    Node(ll X = 0, ll Y = 0): x(X), y(Y), l(0) {
        c[0] = c[1] = NULL;
    }
 
    Node* insert(Node *ins, int child) {
        l++;
        if (!c[child]) {
            c[child] = ins;
            return ins;
        }
        if (ins->x < c[child]->x || ins->y < c[child]->y) {
            ins->c[child] = c[child];
            ins->l += c[child]->l;
            c[child] = ins;
            return ins;
        }
        if (ins->x > c[child]->x || ins->y > c[child]->y) 
            return c[child]->insert(ins, child);
        return c[child];
    }
};
 
int n;
Node *root = new Node();
 
void dfs(Node *curr) {
    ans = min(ans, tot_dist);
    for (int i = 0; i < 2; i++) {
        if (curr->c[i]) {
            ll dx = curr->x - curr->c[i]->x + curr->y - curr->c[i]->y;
            tot_dist += dx * (2 * curr->c[i]->l - n);
            dfs(curr->c[i]);
            tot_dist -= dx * (2 * curr->c[i]->l - n);
        }
    }
}
 
pair<ll, ll> a[100000];
bool cmp(pair<ll, ll> x, pair<ll, ll> y) { return x.first + x.second > y.first + y.second; }
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        tot_dist += a[i].first + a[i].second;
    }
    sort(a, a + n, cmp);
 
    for (int i = 0; i < n; i++) {
        Node *curr = root;
        ll cx = 0, cy = 0;
        for (int j = 29; ~j; j--) {
            if (a[i].first & (1 << j)) {
                cx |= (1 << j);
                curr = curr->insert(new Node(cx, cy), 0);
            } else if (a[i].second & (1 << j)) {
                cy |= (1 << j);
                curr = curr->insert(new Node(cx, cy), 1);
            }
        }
        curr->l++;
    }
    dfs(root);
    cout << ans;
}