#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int cnt[3], ties = 1, streak = 0, curr_scoring = 0, turnover = -1;
bool curr_losing = false, curr_winning = false;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) {
        int x;
        cin >> x;
        cnt[x]++;
        if (cnt[1] == cnt[2]) ties++;

        if (curr_scoring == x) streak++;
        else {
            curr_winning = cnt[3 - x] >= cnt[x];
            if (curr_losing && curr_winning) turnover = max(turnover, streak);
            streak = 1;
            curr_losing = cnt[x] <= cnt[3 - x];
        }

        curr_scoring = x;
    }

    if (curr_losing && curr_winning) turnover = max(turnover, streak);

    cout << cnt[1] << ' ' << cnt[2] << '\n';
    cout << ties << '\n';
    cout << turnover;

    return 0;
}