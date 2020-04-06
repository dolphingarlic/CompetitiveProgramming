#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<pair<int, int>> points;
set<pair<int, int>> point_set;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int a, b;
        cin >> a >> b;
        points.push_back({a, b});
        point_set.insert({a, b});
    }
    int ans = 0;
    sort(points.begin(), points.end());
    for (int i = 0; i < points.size() - 1; i++) {
        for (int j = i + 1; j < points.size(); j++) {
            if (
                (points[i].first == points[j].first &&
                point_set.find({points[i].first + points[j].second - points[i].second, points[i].second}) != point_set.end() &&
                point_set.find({points[i].first + points[j].second - points[i].second, points[j].second}) != point_set.end())) {
                ans++;
                // cout << '{' << points[i].first << ", " << points[i].second << "} and {" << points[j].first << ", " << points[j].second << "}\n";
            }
        }
    }
    cout << ans;
    return 0;
}