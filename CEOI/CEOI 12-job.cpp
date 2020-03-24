#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<int> a[100001];

bool check(int machines, int days, int jobs, int delay, bool output) {
    queue<pair<int, int>> pending;
    FOR(i, 1, days + 1) {
        for (int j : a[i]) pending.push({i, j});

        for (int j = 0; j < machines && pending.size(); j++) {
            if (i - pending.front().first > delay) return false;
            if (output) cout << pending.front().second << ' ';
            pending.pop();
        }

        if (output) cout << "0\n";
    }
    return true;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, d, m;
    cin >> n >> d >> m;
    FOR(i, 1, m + 1) {
        int x;
        cin >> x;
        a[x].push_back(i);
    }

    int l = 1, r = m;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid, n, m, d, false)) r = mid;
        else l = mid + 1;
    }

    cout << l << '\n';
    check(l, n, m, d, true);
    return 0;
}