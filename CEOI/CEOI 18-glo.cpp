#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int dp[200001], a[200001];
vector<int> lis, lds;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    FOR(i, 0, n) {
        cin >> a[i];
        dp[i] = (lis.size() ? lower_bound(lis.begin(), lis.end(), a[i] + m) - lis.begin() : 0);

        int dist = (lis.size() ? lower_bound(lis.begin(), lis.end(), a[i]) - lis.begin() : 0);
        if (dist == lis.size()) lis.push_back(a[i]);
        else lis[dist] = a[i];
    }

    int ans = 0;
    for (int i = n - 1; ~i; i--) {
        int dist = (lds.size() ? lower_bound(lds.begin(), lds.end(), -a[i]) - lds.begin() : 0);
        if (dist == lds.size()) lds.push_back(-a[i]);
        else lds[dist] = -a[i];

        ans = max(ans, dp[i] + dist + 1);
    }

    cout << ans;
    return 0;
}