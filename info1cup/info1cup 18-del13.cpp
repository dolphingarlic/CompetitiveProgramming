/*
InfO(1) Cup 2018 DEL13
- A construction is possible iff it's possible to partition the city into
  M segments such that:
    - Each segment has exactly 1 non-destroyed neighbourhood
    - There are an odd number of neighbourhoods in each segment
- We can use DP and backtracking to construct these segments (see code)
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int p[100002], prv_parity[100002][3];
bool dp[100002][3];
array<int, 3> prv_seg[100002];
vector<int> moves;

void set_dp(int curr, int p1, int p2) {
    if (dp[curr - 1][p2]) {
        dp[curr][p1] = true;
        prv_parity[curr][p1] = p2;
    }
}

void solve(array<int, 3> seg) {
    if (seg[2] == seg[0]) return;
    moves.push_back(seg[1]);
    if (seg[2] - seg[1] == seg[1] - seg[0])
        solve({seg[0] + 1, seg[1], seg[2] - 1});
    else if (seg[2] - seg[1] == 1)
        solve({seg[0], (seg[0] + seg[2] - 2) / 2, seg[2] - 2});
    else if (seg[1] - seg[0] == 1)
        solve({seg[0] + 2, (seg[0] + seg[2] + 2) / 2, seg[2]});
    else
        solve({seg[0] + 1, seg[1], seg[2] - 1});
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 1; i <= m; i++) cin >> p[i];
        p[0] = 0, p[m + 1] = n + 1;

        memset(dp, 0, sizeof dp);
        dp[0][0] = true;
        for (int i = 1; i <= m + 1; i++) {
            if (p[i] - p[i - 1] == 1) set_dp(i, 0, 0);
            else set_dp(i, 0, 1 + (p[i] - p[i - 1]) % 2);

            if ((p[i] - p[i - 1]) % 2 == 0) {
                set_dp(i, 1, 0);
                if (p[i] - p[i - 1] > 2) {
                    set_dp(i, 1, 2);
                    set_dp(i, 2, 1);
                }
            } else if (p[i] - p[i - 1] > 1) {
                set_dp(i, 2, 0);
                set_dp(i, 1, 1);
                if (p[i] - p[i - 1] > 3)
                    set_dp(i, 2, 2);
            }
        }

        if (dp[m + 1][0]) {
            vector<array<int, 3>> segs;
            int parity = 0, boundary;
            for (int i = m + 1; i; i--) {
                if (parity) {
                    if (prv_parity[i][parity]) {
                        segs.push_back({p[i] - parity, p[i], boundary - 1});
                        boundary = p[i] - parity;
                    } else {
                        segs.push_back({p[i - 1] + 1, p[i], boundary - 1});
                        boundary = p[i - 1] + 1;
                    }
                } else boundary = p[i];
                parity = prv_parity[i][parity];
            }

            for (auto i : segs) solve(i);
            cout << moves.size() << '\n';
            while (moves.size()) {
                cout << moves.back() << ' ';
                moves.pop_back();
            }
            cout << '\n';
        } else cout << "-1\n";
    }
    return 0;
}
