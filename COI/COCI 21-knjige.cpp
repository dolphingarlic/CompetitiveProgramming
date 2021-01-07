#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    priority_queue<pair<int, int>> pq;
    set<int> rem;
    for (int i = 1; i <= n; i++) {
        int d;
        cin >> d;
        pq.push({d, i});
        rem.insert(i);
    }
    vector<string> ops;
    while (pq.size()) {
        for (int i : rem) {
            if (i == pq.top().second) {
                ops.push_back("UZMI D L");
            } else {
                ops.push_back("UZMI L L");
                ops.push_back("STAVI L D");
            }
        }
        ops.push_back("STAVI D L");
        rem.erase(pq.top().second);
        pq.pop();
        for (int i : rem) {
            ops.push_back("UZMI L D");
            ops.push_back("STAVI L L");
        }
    }
    cout << ops.size() << '\n';
    for (string i : ops) cout << i << '\n';
    return 0;
}