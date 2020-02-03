#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

queue<int> idx[26];
int bit[1000001], n;

void update(int pos) {
    for (; pos <= n; pos += (pos & (-pos))) bit[pos]++;
}
int query(int pos) {
    int ans = 0;
    for (; pos; pos -= (pos & (-pos))) ans += bit[pos];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    FOR(i, 0, n) {
        char c;
        cin >> c;
        idx[c - 'A'].push(n - i);
    }
    ll ans = 0;
    FOR(i, 0, n) {
        char c;
        cin >> c;
        int pos = idx[c - 'A'].front();
        idx[c - 'A'].pop();
        ans += query(pos);
        update(pos);
    }

    cout << ans;
    return 0;
}