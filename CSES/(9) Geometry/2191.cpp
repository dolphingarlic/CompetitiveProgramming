#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
    ll x, y;

    ll cross(Point A, Point B) {
        return (A.x - x) * (B.y - y) - (A.y - y) * (B.x - x);
    }
};

Point origin = {0, 0}, polygon[1001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> polygon[i].x >> polygon[i].y;
    polygon[n] = polygon[0];
    ll ans = 0;
    for (int i = 0; i < n; i++) ans += origin.cross(polygon[i], polygon[i + 1]);
    cout << abs(ans);
    return 0;
}