#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int apsp[201][201], b[251], c[251], wall[251][251];
vector<int> reg[251];
bool is_club[251];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m, n, l;
    cin >> m >> n >> l;
    FOR(i, 0, l) {
        cin >> c[i];
        is_club[c[i]] = true;
    }

    memset(apsp, 0x3f, sizeof(apsp));
    FOR(i, 1, m + 1) {
        int k;
        cin >> k;
        FOR(j, 0, k) {
            cin >> b[j];
            if (is_club[b[j]]) reg[b[j]].push_back(i);
        }
        FOR(j, 0, k) {
            if (wall[b[j]][b[(j + 1) % k]]) {
                apsp[wall[b[j]][b[(j + 1) % k]]][i] = apsp[i][wall[b[j]][b[(j + 1) % k]]] = 1;
                wall[b[j]][b[(j + 1) % k]] = 0;
            } else wall[b[(j + 1) % k]][b[j]] = i;
        }
        apsp[i][i] = 0;
    }
    FOR(i, 1, n + 1) FOR(j, 1, n + 1) if (wall[i][j]) apsp[wall[i][j]][0] = apsp[0][wall[i][j]] = 1;

    FOR(k, 0, m + 1) FOR(i, 0, m + 1) FOR(j, 0, m + 1)
        apsp[i][j] = min(apsp[i][j], apsp[i][k] + apsp[k][j]);

    pair<int, int> ans = {INT_MAX, 0};
    FOR(i, 1, m + 1) {
        int tot = 0;
        FOR(j, 0, l) {
            int mn = INT_MAX;
            for (int k : reg[c[j]]) mn = min(mn, apsp[k][i]);
            tot += mn;
        }
        ans = min(ans, {tot, i});
    }
    cout << ans.first << '\n' << ans.second;
    return 0;
}