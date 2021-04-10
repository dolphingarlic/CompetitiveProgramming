#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

set<pair<int, int>> all;
set<int> row[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int h, w, n;
    cin >> h >> w >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        all.insert({x, y});
        row[y].insert(x);
    }

    for (int i = 1; i <= h; i++) all.insert({i, w + 1});
    for (int i = 1; i <= w; i++) row[i].insert(h + 1);

    int ans = *row[1].upper_bound(1) - 1, curr_y = 1;
    for (int i = 2; i <= h; i++) {
        if (!all.count({i, curr_y + 1})) curr_y++;
        ans = min(ans, *row[curr_y].upper_bound(i) - 1);
    }
    cout << ans;
    return 0;
}
