/*
Baltic 2011 Polygon
- Ans = 2 * (Polygon area) - (Sum of horizontal and vertical edges) / 2
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

struct Point { ll x, y; } v[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    ll d_ans = 0;
    cin >> n;
    FOR(i, 0, n) {
        cin >> v[i].x >> v[i].y;
        if (i) d_ans += v[i].x * v[i - 1].y - v[i - 1].x * v[i].y;
    }
    d_ans += v[0].x * v[n - 1].y - v[n - 1].x * v[0].y;
    d_ans = 2 * abs(d_ans);

    FOR(i, 1, n) {
        if (v[i].x == v[i - 1].x) d_ans -= abs(v[i].y - v[i - 1].y);
        if (v[i].y == v[i - 1].y) d_ans -= abs(v[i].x - v[i - 1].x);
    }
    if (v[0].x == v[n - 1].x) d_ans -= abs(v[0].y - v[n - 1].y);
    if (v[0].y == v[n - 1].y) d_ans -= abs(v[0].x - v[n - 1].x);

    cout << d_ans / 2 << (d_ans & 1 ? ".5" : "");
    return 0;
}