#include <bits/stdc++.h>
using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    int n, m;
    cin >> m >> n;
    
    int ans = 0, lptr = -1, rptr;
    deque<pair<int, int>> mn, mx;
    for (rptr = 0; rptr < n; rptr++) {
        int x;
        cin >> x;
        while (mn.size() && mn.back().first >= x) mn.pop_back();
        while (mx.size() && mx.back().first <= x) mx.pop_back();
        mn.push_back({x, rptr}); mx.push_back({x, rptr});
        
        while (mx.size() && mn.size() && mx[0].first - mn[0].first > m) {
            lptr++;
            if (mn[0].second == lptr) mn.pop_front();
            if (mx[0].second == lptr) mx.pop_front();
        }
        
        ans = max(ans, rptr - lptr);
    }
    
    cout << ans;
    return 0;
}
