/*
COI 2019 Segway
- The constraints are all pretty small, so you can just brute force everything
- Complexity: O(1500 * N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int a[20000], b[20000], c[20000], cnt[301], pos[20000], ans[20000], boost[20000];
vector<int> riders[51];
bool to_check[301];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i] >> c[i];
        riders[a[i]].push_back(i);
    }
    int m;
    cin >> m;
    while (m--) {
        int d;
        cin >> d;
        to_check[d] = true;
    }
    int now = 0;
    while (cnt[300] < n) {
        now++;
        for (int i : riders[now % 51]) {
            pos[i]++;
            if (to_check[pos[i]] && !boost[i]) boost[i] = cnt[pos[i]] % 20;

            if (pos[i] == 300) ans[i] = now;
            else if (boost[i]) {
                boost[i]--;
                riders[(now + 1) % 51].push_back(i);
            } else {
                int nxt;
                if (pos[i] < 100) nxt = (now + a[i]) % 51;
                else if (pos[i] < 200) nxt = (now + b[i]) % 51;
                else nxt = (now + c[i]) % 51;
                riders[nxt].push_back(i);
            }
        }
        for (int i : riders[now % 51]) cnt[pos[i]]++;
        riders[now % 51].clear();
    }
    for (int i = 0; i < n; i++) cout << ans[i] << '\n';
    return 0;
}