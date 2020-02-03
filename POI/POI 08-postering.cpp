#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

pair<int, int> buildings[250001];

int bit[250001], n;
void update(int pos) {
    for (; pos <= n; pos += (pos & (-pos))) bit[pos]++;
}
int query(int a, int b) {
    int ans = 0;
    for (; b; b -= (b & (-b))) ans += bit[b];
    for (a--; a; a -= (a & (-a))) ans -= bit[a];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n + 1) {
        int x;
        cin >> x >> buildings[i].first;
        buildings[i].second = i;
    }
    sort(buildings + 1, buildings + n + 1);

    int ans = 1;
    FOR(i, 1, n) {
        if (buildings[i].first == buildings[i + 1].first) {
            if (query(buildings[i].second, buildings[i + 1].second)) ans++;
        } else ans++;
        update(buildings[i].second);
    }

    cout << ans;
    return 0;
}