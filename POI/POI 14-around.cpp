#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll l[2000000], idx[2000000], dst[2000000];
int visited[2000000], ans[100];
pair<int, int> p[100];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, s;
    cin >> n >> s;
    FOR(i, 0, n) {
        cin >> l[i];
        l[n + i] = l[i];
        idx[i] = i;
        idx[n + i] = n + i;
    }
    FOR(i, 0, s) {
        cin >> p[i].first;
        p[i].second = i;
    }
    sort(p, p + s);

    memset(visited, 0x3f, sizeof(visited));
    visited[0] = 0;
    FOR(i, 0, s) {
        ans[p[i].second] = INT_MAX;

        FOR(j, 0, 2 * n) {
            if (visited[j] > 2 * n) ans[p[i].second] = -1;
            else {
                while (idx[j] < 2 * n && dst[j] + l[idx[j]] <= p[i].first) {
                    dst[j] += l[idx[j]++];
                    visited[idx[j]] = min(visited[idx[j]], visited[j] + 1);
                }
            }
        }

        for (int j = n - 1; ~j; j--) {
            ans[p[i].second] = min(ans[p[i].second], visited[j + n] - visited[j]);
            if (idx[j] == j) ans[p[i].second] = -1;
        }

        cout << p[i].first << '\n';
        FOR(j, 0, 2 * n) cout << idx[j] << ' ';
        cout << '\n';
        FOR(j, 0, 2 * n) cout << visited[j] << ' ';
        cout << '\n';
    }

    FOR(i, 0, s) {
        if (ans[i] == -1) cout << "NIE\n";
        else cout << ans[i] << '\n';
    }
    return 0;
}