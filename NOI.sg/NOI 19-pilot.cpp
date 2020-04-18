#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll curr = 0, sz[1000002], ans[1000002];
int cmp[1000002];

int find(int A) {
    while (A != cmp[A]) A = cmp[A], cmp[A] = cmp[cmp[A]];
    return A;
}

void onion(int A, int B) {
    A = find(A), B = find(B);
    curr += sz[A] * sz[B];
    sz[A] += sz[B];
    cmp[B] = A;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> events;
    FOR(i, 1, n + 1) {
        int h;
        cin >> h;
        events.push_back({h, -i});
    }
    FOR(i, 1, q + 1) {
        int h;
        cin >> h;
        events.push_back({h, i});
    }
    sort(events.begin(), events.end());

    for (pair<int, int> i : events) {
        if (i.second > 0) ans[i.second] = curr;
        else {
            curr++;
            cmp[-i.second] = -i.second;
            sz[-i.second] = 1;
            if (cmp[-i.second - 1]) onion(-i.second, -i.second - 1);
            if (cmp[-i.second + 1]) onion(-i.second, -i.second + 1);
        }
    }

    FOR(i, 1, q + 1) cout << ans[i] << '\n';
    return 0;
}