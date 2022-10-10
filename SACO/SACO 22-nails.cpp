#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

pair<int, int> banners[300001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> banners[i].second >> banners[i].first;
    sort(banners, banners + n);
    vector<int> ans;
    int last_covered = 0;
    for (int i = 0; i < n; i++) {
        if (banners[i].second > last_covered) {
            last_covered = banners[i].first;
            ans.push_back(last_covered);
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans) cout << i << ' ';
    return 0;
}
