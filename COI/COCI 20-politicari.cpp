/*
COCI 2020 Politicari
- Basically we want to find a loop and output the k-th element
  of that loop
- Complexity: O(N^2)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[501][501], nxt[501][501];
bool visited[501][501];

vector<int> tail, cycle;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    ll m;
    cin >> n >> m;
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) cin >> a[i][j];

    pair<int, int> curr = {1, 2};
    while (true) {
        if (visited[curr.second][curr.first]) {
            pair<int, int> here = {1, 2};
            tail.push_back(1);
            while (here != curr) {
                tail.push_back(here.second);
                here = {here.second, a[here.second][here.first]};
            }
            cycle.push_back(here.second);
            here = {here.second, a[here.second][here.first]};
            while (here != curr) {
                cycle.push_back(here.second);
                here = {here.second, a[here.second][here.first]};
            }
            break;
        } else {
            visited[curr.second][curr.first] = true;
            curr = {curr.second, a[curr.second][curr.first]};
        }
    }

    if (m <= tail.size()) cout << tail[m - 1];
    else cout << cycle[(m - tail.size() - 1) % cycle.size()];
    return 0;
}