#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const long double PI = 4 * atan(1);
ll v[100000];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cin >> n;
    FOR(i, 0, n) cin >> v[i];
    cout << fixed << setprecision(4) << (v[0] * v[0] * n) / (4 * tan(PI / n));
    return 0;
}