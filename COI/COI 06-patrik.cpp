#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    ll ans = 0;
    vector<int> v;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x;

        int l = 0, r = v.size() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (v[mid] > x) l = mid + 1;
            else r = mid;
        }

        if (r == -1) ans = 0;
        else if (v[l] > x || l == 0) ans += (v.size() - l);
        else ans += (v.size() - l + 1);

        while (v.size() && v.back() < x) v.pop_back();
        v.push_back(x);
    }
    
    cout << ans;
    return 0;
}