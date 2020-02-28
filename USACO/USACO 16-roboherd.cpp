/*
USACO 2016 Roboherd
- Instead of trying to find the robots individually, let us try find the number of robots
  we can make that cost at most X dollars
    - To do this, we use a pruned brute-force search
    - See code for more details
- Notice how the number of robots we can make is non-decreasing as K increases, so we can
  binary search for the optimal X
- After we find the minimum X such that we can make K robots, we can repeat the brute-force
  search to find the total cost
- Complexity: O(N log MAX_V)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, k, cnt;
vector<ll> parts[100000];
ll v[100000], by_diff[100000], save = 0;

void search(int x, ll budget) {
    if (cnt >= k) return;
    if (~x && budget < parts[x][0]) x = upper_bound(by_diff, by_diff + x, budget) - by_diff - 1;
    if (~x) {
        search(x - 1, budget);
        for (int i = 0; i < parts[x].size() && parts[x][i] <= budget; i++) search(x - 1, budget - parts[x][i]);
    } else cnt++;
}

void calc_savings(int x, ll budget) {
    if (~x && budget < parts[x][0]) x = upper_bound(by_diff, by_diff + x, budget) - by_diff - 1;
    if (~x) {
        calc_savings(x - 1, budget);
        for (int i = 0; i < parts[x].size() && parts[x][i] <= budget; i++) calc_savings(x - 1, budget - parts[x][i]);
    } else save += budget + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ifstream cin("roboherd.in");
    ofstream cout("roboherd.out");

    ll base = 0, l = 0, r = 0;
    cin >> n >> k;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        FOR(j, 0, x) cin >> v[j];
        sort(v, v + x);

        base += v[0];
        if (x == 1) {
            n--;
            i--;
        } else {
            FOR(j, 1, x) parts[i].push_back(v[j] - v[0]);
            r += parts[i].back();
        }
    }
    sort(parts, parts + n);
    FOR(i, 0, n) by_diff[i] = parts[i][0];

    while (l != r) {
        ll mid = (l + r) / 2;
        cnt = 0;
        search(n - 1, mid);
        if (cnt < k) l = mid + 1;
        else r = mid;
    }

    if (l > 0) calc_savings(n - 1, l - 1);
    cout << (base + l) * k - save << '\n';
    return 0;
}