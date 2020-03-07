#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

deque<int> has[9];
vector<pair<int, int>> contrib = {{0, 0}, {1, 1},  {1, -1}, {-1, 1}, {-1, -1},
                                  {0, 1}, {0, -1}, {1, 0},  {-1, 0}};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, l = 0, r = 0;
    cin >> n;
    FOR(i, 0, n) {
        int t, v;
        cin >> t >> v;
        has[t].push_back(v);
        l += contrib[t].first, r += contrib[t].second;
    }
    FOR(i, 1, 9) sort(has[i].begin(), has[i].end());

    if (l != -r) {
        cout << -1;
    } else {
        int nxt = 0;
        if (has[5].size()) {
            cout << has[5].front() << ' ';
            nxt = contrib[5].second;
        } else {
            cout << has[6].front() << ' ';
            nxt = contrib[6].second;
        }

        FOR(i, 2, n) {
            if (nxt == 1) {
                if ((has[4].empty() ||
                     (has[3].size() && has[3].front() < has[4].front())) &&
                    (i + has[3].size() == n || (has[1].size() || has[2].size()))) {
                    cout << has[3].front() << ' ';
                    has[3].pop_front();
                    nxt = contrib[3].second;
                } else {
                    cout << has[4].front() << ' ';
                    has[4].pop_front();
                    nxt = contrib[4].second;
                }
            } else {
                if ((has[2].empty() ||
                     (has[1].size() && has[1].front() < has[2].front())) &&
                    (i + has[1].size() == n || (has[3].size() || has[4].size()))) {
                    cout << has[1].front() << ' ';
                    has[1].pop_front();
                    nxt = contrib[1].second;
                } else {
                    cout << has[2].front() << ' ';
                    has[2].pop_front();
                    nxt = contrib[2].second;
                }
            }
        }

        if (has[7].size()) {
            cout << has[7].front();
        } else {
            cout << has[8].front();
        }
    }
    return 0;
}