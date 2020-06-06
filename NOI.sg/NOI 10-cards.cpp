/*
NOI.sg 2010 Cards
- Just use a deque
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    string s;
    cin >> n >> k >> s;

    deque<int> dq;
    FOR(i, 0, n) dq.push_back(i);
    for (char c : s) {
        if (c == 'A') {
            dq.push_back(dq[0]);
            dq.pop_front();
        } else if (c == 'B') {
            int tmp = dq[0];
            dq.push_back(dq[1]);
            dq.pop_front(); dq.pop_front();
            dq.push_front(tmp);
        }
    }
    cout << dq[k - 1] << ' ' << dq[k] << ' ' << dq[k + 1];
    return 0;
}