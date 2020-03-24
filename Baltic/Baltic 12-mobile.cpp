#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define x first
#define y second
using namespace std;

pair<double, double> p[1000000];
pair<double, int> contacts[2000000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    double len;
    cin >> n >> len;
    FOR(i, 0, n) cin >> p[i].x >> p[i].y;

    double l = 1, r = 5e8;
    while (r - l > 1e-4) {
        double mid = (l + r) / 2;

        int cnt = 0;
        FOR(i, 0, n) {
            if (mid < abs(p[i].y)) continue;
            double delta = sqrt(mid * mid - p[i].y * p[i].y);
            contacts[cnt++] = {p[i].x - delta, 1};
            contacts[cnt++] = {p[i].x + delta, -1};
        }
        contacts[cnt++] = {0.0, 0};
        contacts[cnt++] = {len, 0};
        sort(contacts, contacts + cnt);

        int active = 0;
        bool good = true;
        FOR(i, 0, cnt) {
            active += contacts[i].y;
            if (contacts[i].x > len) break;
            if (contacts[i].x < 0) continue;
            if (active == 0) {
                good = false;
                break;
            }
        }
        if (good) r = mid;
        else l = mid;
    }

    cout << fixed << setprecision(3) << l;
    return 0;
}