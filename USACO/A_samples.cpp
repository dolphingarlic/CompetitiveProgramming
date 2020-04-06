#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

vector<pair<int, int>> can;
int fertile[100][100];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("sprinklers2.in");
    ofstream cout("sprinklers2.out");
    int n;
    cin >> n;
    FOR(i, 0, n) FOR(j, 0, n) {
        char c;
        cin >> c;
        if (c == '.') can.push_back({i, j});
    }

    int ans = 0;
    FOR(mask, 0, pow(3, can.size())) {
        FOR(i, 0, n) FOR(j, 0, n) fertile[i][j] = 1;

        int temp = mask;
        FOR(i, 0, can.size()) {
            if (temp % 3 == 1) {
                FOR(j, can[i].first, n) FOR(k, 0, can[i].second + 1) fertile[j][k] *= 2;
            } else if (temp % 3 == 2) {
                FOR(j, 0, can[i].first + 1) FOR(k, can[i].second, n) fertile[j][k] *= 3;
            }
            temp /= 3;
        }
        bool good = true;
        FOR(i, 0, n) FOR(j, 0, n) if (fertile[i][j] % 6 == 0 || fertile[i][j] == 1) good = false;

        ans += good;
    }
    cout << ans << '\n';
    return 0;
}