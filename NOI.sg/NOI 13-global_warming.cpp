#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int n, i, a, b, w[2010000], c, S, R;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    b = 0;
    for (i = 1; i <= n; i++) {
        cin >> a;
        if (a > b) w[c++] = b * 2, w[c++] = a * 2 - 1;
        b = a;
    }
    sort(w, w + c);
    for (i = 0; i < c; i++) {
        S += (w[i] & 1) ? -1 : 1;
        if (R < S) R = S;
    }
    cout << R;
}