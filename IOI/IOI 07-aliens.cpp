#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n;

bool inside(int x, int y) { return (x > 0 && y > 0 && x <= n && y <= n); }

bool get(int x, int y) {
    if (!inside(x, y)) return false;
    cout << "examine " << x << ' ' << y << endl;
    string s;
    cin >> s;
    return (s[0] == 't');
}

int boundary(int x, int y, int dx, int dy) {
    bool fits = true;
    int len = 0;
    for (; fits && inside(x + dx * (1 << len), y + dy * (1 << len)); len++)
        fits = get(x + dx * (1 << len), y + dy * (1 << len));
    int ret = 0;
    for (len -= 1 + !fits; ~len; len--) {
        if (get(x + dx * (ret + (1 << len)), y + dy * (ret + (1 << len))))
            ret += (1 << len);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int x, y;
    cin >> n >> x >> y;

    int r = boundary(x, y, 1, 0), l = boundary(x, y, -1, 0), b = boundary(x, y, 0, -1);

    int sz = r + l + 1;
    int mx = x - l + sz / 2, my = y - b + sz / 2;

    while (get(mx + 2 * sz, my)) mx += 2 * sz;
    while (get(mx, my + 2 * sz)) my += 2 * sz;
    while (get(mx + sz, my + sz)) mx += sz, my += sz;

    cout << "solution " << mx - 2 * sz << ' ' << my - 2 * sz << endl;
    return 0;
}