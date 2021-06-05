/*
InfO(1) Cup 2020 Football
- If the total number of players is odd, then Little Square just picks 1
  player as his first move and wins
- Otherwise, he picks an even number of players and whoever picks the first
  odd number of players loses
- We can therefore effectively divide all player counts by 2 and rerun the
  solution above
- Note that this means that the two players in this game will always pick
  powers of 2 (hence the second-last subtask)
- Complexity: O(sum(N log K))
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cnt[100001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) cin >> cnt[i];
        int winner = 0;
        for (int kk = 1; kk <= k; kk <<= 1) {
            int nimber = 0;
            for (int i = 1; i <= n; i++) nimber ^= cnt[i] & kk;
            if (nimber) winner = 1;
        }
        cout << winner;
    }
    return 0;
}
