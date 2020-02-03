/*
POI 2005 Toy Cars
- Basically just computing the swap sequence for IOI 2012 Last Supper
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

set<pair<int, int>> scaffold;
vector<int> occurrences[100001];
bool on_floor[100001];
int C[500000];

int nxt(int colour, int curr) {
    auto it = upper_bound(occurrences[colour].begin(), occurrences[colour].end(), curr);
    if (it == occurrences[colour].end()) return 1e9;
    return *it;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int N, K, P, ans = 0;
    cin >> N >> K >> P;

    FOR(i, 0, P) {
        cin >> C[i];
        C[i];
        occurrences[C[i]].push_back(i);
    }

    FOR(i, 0, P) {
        if (on_floor[C[i]]) {
            scaffold.erase({i, C[i]});
        } else {
            if (scaffold.size() == K) {
                on_floor[(*scaffold.rbegin()).second] = false;
                scaffold.erase(--scaffold.end());
            }
            ans++;
        }
        scaffold.insert({nxt(C[i], i), C[i]});
        on_floor[C[i]] = true;
    }

    cout << ans;
    return 0;
}