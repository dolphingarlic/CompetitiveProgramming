/*
LMIO 2019 Triusis
- First, subtract M * i from the i-th pole
- Now we simply need to find the minimum number of poles we need to remove
  so that the remaining poles form a decreasing sequence
- Notice how this is simple N - (LDS of the poles)
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<ll> lis = {0};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        int h;
        cin >> h;
        ll v = -h + m * i;
        if (v < 0) continue;
        int ub = upper_bound(lis.begin(), lis.end(), v) - lis.begin();
        if (ub == lis.size()) lis.push_back(v);
        else lis[ub] = v;
    }
    cout << n - lis.size() + 1;
    return 0;
}