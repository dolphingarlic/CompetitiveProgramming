#include <bits/stdc++.h>
#pragma GCC Optimize("unroll-loops")
#pragma GCC Optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Node {
    Node *l, *r;
    int sum;

    Node(int val) {
        l = nullptr, r = nullptr;
        sum = val;
    }
    Node(Node *ll, Node *rr) {
        l = ll, r = rr;
        sum = 0;
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
};

string s;
int n, x[100001], y[100001];
Node* persist_roots[26][100001];

Node* build(char k, int l = 1, int r = n) {
    if (l == r) return new Node(s[l - 1] == k);
    int mid = (l + r) >> 1;
    return new Node(build(k, l, mid), build(k, mid + 1, r));
}
int query(Node* node, int a, int b, int l = 1, int r = n) {
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) return node->sum;
    int mid = (l + r) >> 1;
    return query(node->l, a, b, l, mid) + query(node->r, a, b, mid + 1, r);
}
Node* update(Node* node, int pos, int l = 1, int r = n) {
    if (l == r) return new Node(0);
    int mid = (l + r) >> 1;
    if (pos > mid) return new Node(node->l, update(node->r, pos, mid + 1, r));
    else return new Node(update(node->l, pos, l, mid), node->r);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int q;
    cin >> s >> q;
    n = s.size();
    FOR(i, 0, q) cin >> x[i] >> y[i];
    FOR(i, 0, 26) persist_roots[i][0] = build((char)(i + 'a'));

    FOR(i, 1, n + 1) {
        int pos;
        cin >> pos;
        FOR(j, 0, 26) persist_roots[j][i] = persist_roots[j][i - 1];
        persist_roots[s[pos - 1] - 'a'][i] = update(persist_roots[s[pos - 1] - 'a'][i - 1], pos);
    }

    int l = 0, r = n;
    while (l != r) {
        int mid = (l + r) >> 1;
        bool possible = true;
        FOR(i, 0, q) {
            FOR(j, 0, 26) {
                if (query(persist_roots[j][mid], x[i], y[i]) > 1) {
                    possible = false;
                    break;
                }
            }
        }
        if (possible) r = mid;
        else l = mid + 1;
    }
    cout << l;
    return 0;
}