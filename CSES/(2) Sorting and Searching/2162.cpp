#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int nxt[200001];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    if (n == 1) return cout << 1, 0;
    for (int i = 0; i < n; i++) nxt[i] = (i + 1) % n;
    int curr = 1, prv = 0;
    for (int i = 0; i < n; i++) {
        cout << curr + 1 << ' ';
        nxt[prv] = nxt[curr];
        prv = nxt[curr];
        curr = nxt[nxt[curr]];
    }
    return 0;
}