#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int v[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> v[i];
    long double s = (v[0] + v[1] + v[2] + v[3]) / 2.0;
    cout << fixed << setprecision(4) << sqrt((s - v[0]) * (s - v[1]) * (s - v[2]) * (s - v[3]));
    return 0;
}