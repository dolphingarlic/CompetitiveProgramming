#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int lis = 0;
pair<int, int> a[100000];
set<int> s;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i].first >> a[i].second;
    sort(a, a + n, greater<pair<int, int>>());

    FOR(i, 0, n) {
        if (s.upper_bound(a[i].second) == s.end()) lis++;
        else s.erase(s.upper_bound(a[i].second));
        s.insert(a[i].second);
    }

    cout << lis;
    return 0;
}