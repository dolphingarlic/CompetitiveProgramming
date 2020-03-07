#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Edge {
    int l, r, c;
    Edge operator+(Edge b) {
        return {l, b.r, 6 - c - b.c};
    }
};

Edge polygon[200000];
vector<Edge> diagonal;
int lptr = 0, rptr = 1;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    string s;
    cin >> s;
    FOR(i, 0, n) {
        polygon[i] = {i % n + 1, (i + 1) % n + 1, s[i] - '1' + 1};
    }

    for (; rptr < n - 1; rptr++) {
        if (polygon[rptr].c != polygon[lptr].c) {
            for (int i = rptr - 1; i >= lptr && (polygon[rptr].r != n || polygon[i].l != 1); i--) {
                diagonal.push_back(polygon[i] + polygon[rptr]);
                polygon[rptr] = polygon[i] + polygon[rptr];
            }
            lptr = rptr;
        }
    }

    set<int> st;
    FOR(i, rptr - 2, n) st.insert(polygon[i].c);
    if (st.size() != 3) cout << "NE\n";
    else {
        cout << "DA\n";
        for (Edge i : diagonal) cout << i.l << ' ' << i.r << ' ' << i.c << '\n';
    }
    return 0;
}