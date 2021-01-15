#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

struct Point {
    ll x, y;

    ll cross(Point A, Point B) {
        return (A.x - x) * (B.y - y) - (A.y - y) * (B.x - x);
    }

    bool operator<(Point B) {
        if (x == B.x) return y < B.y;
        return x < B.x;
    }
} p[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> p[i].x >> p[i].y;
    sort(p, p + n);
    vector<int> upper;
    for (int i = 0; i < n; i++) {
        while (upper.size() > 1 && p[upper.back()].cross(p[upper[upper.size() - 2]], p[i]) > 0)
            upper.pop_back();
        upper.push_back(i);
    }
    vector<int> lower;
    for (int i = n - 1; ~i; i--) {
        while (lower.size() > 1 && p[lower.back()].cross(p[lower[lower.size() - 2]], p[i]) > 0)
            lower.pop_back();
        lower.push_back(i);
    }
    upper.pop_back(); lower.pop_back();
    upper.insert(upper.end(), lower.begin(), lower.end());
    cout << upper.size() << '\n';
    for (int i : upper) cout << p[i].x << ' ' << p[i].y << '\n';
    return 0;
}