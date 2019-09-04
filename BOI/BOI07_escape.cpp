#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

pair<int, int> a[251];
vector<int> graph[252];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int l, w, n;
    cin >> l >> w >> n;
    FOR(i, 1, n + 1) {
        cin >> a[i].first >> a[i].second;
    }

    FOR(i, 1, n + 1) {
        if (a[i].second - 100 <= 0) graph[0].push_back(i);
        if (a[i].second + 100 >= w) graph[n + 1].push_back(i);
        FOR(j, i + 1, n + 1) {
            if ((a[i].first - a[j].first) * (a[i].first - a[j].first) + (a[i].second - a[j].second) * (a[i].second - a[j].second) <= 100) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    return 0;
}