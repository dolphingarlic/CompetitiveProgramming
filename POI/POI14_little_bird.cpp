#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#pragma GCC Optimizez("unroll-loops")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int a[1000005];
int visited[1000005]{1};

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    
    int q;
    cin >> q;
    while (q--) {
        int k;
        cin >> k;

        fill(visited + 1, visited + n, 0);
        deque<int> q;
        q.push_back(0);
        while (!q.empty()) {
            int curr = q.front();
            q.pop_front();

            FOR(i, 1, min(n - curr + 1, k + 1)) {
                if (visited[curr + i] == 0 || visited[curr + i] - visited[curr] > 1) {
                    visited[curr + i] = visited[curr] + (a[curr] <= a[curr + i]);
                    if (a[curr] > a[curr + i]) q.push_front(curr + i);
                    else q.push_back(curr + i);
                }
            }
        }

        cout << visited[n - 1] - 1 << '\n';
    }
    return 0;
}