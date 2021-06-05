/*
InfO(1) Cup 2020 Trampolines
- It's optimal to use the closest available green trampoline when moving
  down the grid
- We can use binary search to find the closest green trampoline for each
  green trampoline
- Next, we use binary jumping to find the shortest path from row i to j
- If the shortest path is good enough, we answer "Yes"
- Complexity: O((T + N) log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

map<int, set<pair<int, int>>> trampolines;
int a[200001], b[200001], nxt[200001][20];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int r, c, n;
    cin >> r >> c >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
        trampolines[-a[i]].insert({b[i], i});
    }
    for (auto &i : trampolines) {
        for (pair<int, int> j : i.second) {
            auto lb = trampolines[i.first - 1].lower_bound({j.first, 0});
            if (lb != trampolines[i.first - 1].end()) {
                nxt[j.second][0] = lb->second;
                for (int k = 1; k < 20; k++)
                    nxt[j.second][k] = nxt[nxt[j.second][k - 1]][k - 1];
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2 || y1 > y2) {
            cout << "No\n";
            continue;
        }
        if (x1 == x2) {
            cout << "Yes\n";
            continue;
        }
        auto lb = trampolines[-x1].lower_bound({y1, 0});
        if (lb == trampolines[-x1].end()) {
            cout << "No\n";
            continue;
        }
        int rem = x2 - x1 - 1;
        int curr = lb->second;
        for (int i = 0; i < 20; i++) if (rem & (1 << i))
            curr = nxt[curr][i];
        if (curr && b[curr] <= y2) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
