#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
typedef long long ll;
using namespace std;

int has_cow[601][601], h_pref[601][601], v_pref[601][601];

pair<int, int> cows[90000];
int cnt = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ifstream cin("triangles.in");
    ofstream cout("triangles.out");

    int n;
    cin >> n;
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) {
        char c;
        cin >> c;
        if (c == '*') {
            cows[cnt++] = {i + j - 1, i - j + n};
            has_cow[i + j - 1][i - j + n] = 1;
        }
    }
    sort(cows, cows + cnt);
    n *= 2;

    FOR(i, 1, n) FOR(j, 1, n) {
        v_pref[i][j] = v_pref[i - 1][j] + has_cow[i][j];
        h_pref[i][j] = h_pref[i][j - 1] + has_cow[i][j];
    }

    int ans = 0;
    FOR(i, 0, cnt) FOR(j, i + 1, cnt) {
        int x1 = cows[i].first, y1 = cows[i].second, x2 = cows[j].first, y2 = cows[j].second;
        if (x1 == x2) {
            int d = y2 - y1;
            if (x1 > d)
                ans += h_pref[x1 - d][y2] - h_pref[x1 - d][y1 - 1];
            if (x1 + d < n)
                ans += h_pref[x1 + d][y2] - h_pref[x1 + d][y1 - 1];
        } else if (y1 == y2) {
            int d = x2 - x1;
            if (y1 > d)
                ans += v_pref[x2][y1 - d] - v_pref[x1 - 1][y1 - d];
            if (y1 + d < n)
                ans += v_pref[x2][y1 + d] - v_pref[x1 - 1][y1 + d];
        } else {
            if (y1 < y2) {
                if (y2 - y1 > x2 - x1) {
                    if (x2 > y2 - y1)
                        ans += has_cow[x2 - y2 + y1][y2];
                    if (x1 + y2 - y1 < n)
                        ans += has_cow[x1 + y2 - y1][y1];
                } else {
                    if (y2 > x2 - x1)
                        ans += has_cow[x2][y2 - x2 + x1];
                    if (y1 + x2 - x1 < n)
                        ans += has_cow[x1][y1 + x2 - x1];
                }
            } else {
                if (y1 - y2 > x2 - x1) {
                    if (x2 > y1 - y2)
                        ans += has_cow[x2 - y1 + y2][y2];
                    if (x1 + y2 - y1 < n)
                        ans += has_cow[x1 + y1 - y2][y1];
                } else {
                    if (y1 > x2 - x1)
                        ans += has_cow[x1][y1 - x2 + x1];
                    if (y2 + x2 - x1 < n)
                        ans += has_cow[x2][y2 + x2 - x1];
                }
            }
        }
    }
    cout << ans / 3;
    return 0;
}