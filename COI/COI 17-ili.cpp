#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int known[20001];
bool val[20001];
vector<int> bck[20001], fwd[20001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    deque<int> dq;
    for (int i = 1; i <= m; i++) {
        char c;
        cin >> c;
        if (c == '0') {
            known[i] = 2;
            val[i] = 0;
            dq.push_front(i);
        } else if (c == '1') {
            known[i] = 2;
            val[i] = 1;
            dq.push_back(i);
        }
    }
    for (int i = 1; i <= m; i++) {
        char c1, c2;
        int u1, u2;
        cin >> c1 >> u1 >> c2 >> u2;
        if (c1 == 'x') u1 += m;
        if (c2 == 'x') u2 += m;
        bck[i].push_back(u1);
        bck[i].push_back(u2);
        fwd[u1].push_back(i);
        fwd[u2].push_back(i);
    }
    while (dq.size()) {
        int curr = dq.front();
        cout << curr << ' ' << val[curr] << endl;
        dq.pop_front();
        if (val[curr]) {
            for (int i : fwd[curr]) if (known[i] != 2) {
                known[i] = 2;
                val[i] = 1;
                dq.push_back(i);
            }
            if (curr <= m) {
                if (known[bck[curr][0]] == 2 && known[bck[curr][1]] != 2 && !val[bck[curr][0]]) {
                    known[bck[curr][1]] = 2;
                    val[bck[curr][1]] = 1;
                    dq.push_back(bck[curr][1]);
                }
                if (known[bck[curr][1]] == 2 && known[bck[curr][0]] != 2 && !val[bck[curr][1]]) {
                    known[bck[curr][0]] = 2;
                    val[bck[curr][0]] = 1;
                    dq.push_back(bck[curr][0]);
                }
            }
        } else {
            for (int i : bck[curr]) if (known[i] != 2) {
                known[i] = 2;
                val[i] = 0;
                dq.push_front(i);
            }
            for (int i : fwd[curr]) if (known[i] != 2) {
                known[i]++;
                if (known[i] == 2) {
                    if (val[i]) dq.push_back(i);
                    else dq.push_front(i);
                }
            }
        }
    }
    for (int i = 1; i <= m; i++) {
        if (known[i] == 2) cout << val[i];
        else cout << '?';
    }
    return 0;
}
