/*
COI 2009 Loza
- We only care about the horizontal links
- Build the tree from the bottom up
- For each node, let the relative position of its '+' be 0 and for
  each child level, store the relative span of that level
    - We can use a vector pointer to quickly push the list up to a parent
- After we finish processing a node, also add its left and right sides as a span
- If a node has no children, do nothing
- If a node has 1 child, that node inherits the child's span list
- If a node has 2 children, calculate the distance one of the subtrees
  must move by going through each child level up to the minimum depth between them
    - Then just move each span that amount
- Since if there are many such nodes, the tree is shallow, and vice versa, this is efficient
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    int c, l_len, r_len;
    Node *l, *r;

    int x;
    vector<pair<int, int>> *span;
} a[300001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 1, n + 1) {
        string s;
        cin >> s;
        a[i].l_len = (s.size() + 1) / 2;
        a[i].r_len = (s.size() + 2) / 2;

        if (i > 1) {
            int p;
            cin >> p;
            if (!a[p].c++) a[p].l = &a[i];
            else a[p].r = &a[i];
        }
    }

    ll ans = 0;
    for (int i = n; i; i--) {
        ans += 3 * (a[i].l_len + a[i].r_len + 1);

        if (!a[i].c) {
            a[i].span = new vector<pair<int, int>>();
            a[i].x = 0;
        } else if (a[i].c == 1) {
            a[i].span = a[i].l->span;
            a[i].x = a[i].l->x;
            ans += 3;
        } else {
            vector<pair<int, int>> *l_span = a[i].l->span;
            vector<pair<int, int>> *r_span = a[i].r->span;
            int mn = min(l_span->size(), r_span->size());

            int width = INT_MIN;
            FOR(j, 1, mn + 1)
                width = max(width, (*l_span)[l_span->size() - j].second - (*r_span)[r_span->size() - j].first + 1);

            if ((width & 1) == ((a[i].l->x & 1) == (a[i].r->x & 1))) width++;

            if (l_span->size() < r_span->size()) {
                a[i].span = r_span;
                a[i].l->x -= width;
                FOR(j, 0, mn) {
                    (*l_span)[j].first -= width;
                    (*l_span)[j].second -= width;
                }
            } else {
                a[i].span = l_span;
                a[i].r->x += width;
                FOR(j, 0, mn) {
                    (*r_span)[j].first += width;
                    (*r_span)[j].second += width;
                }
            }

            FOR(j, 1, mn + 1) {
                (*r_span)[r_span->size() - j].first = (*l_span)[l_span->size() - j].first;
                (*l_span)[l_span->size() - j].second = (*r_span)[r_span->size() - j].second;
            }
            a[i].x = (a[i].r->x + a[i].l->x) / 2;

            ans += 4 + a[i].r->x - a[i].l->x;
        }

        a[i].span->push_back({a[i].x - a[i].l_len, a[i].x + a[i].r_len});
    }

    cout << ans;
    return 0;
}