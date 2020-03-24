#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int n, k, r;
int a[200001], req[200001], cnt[200001];

bool check(int len) {
    int num_fulfilled = 0;
    fill(cnt, cnt + n, 0);
    FOR(i, 0, len) {
        cnt[a[i]]++;
        if (cnt[a[i]] == req[a[i]]) num_fulfilled++;
    }
    if (num_fulfilled == r) return true;

    FOR(i, len, n) {
        if (cnt[a[i - len]] == req[a[i - len]]) num_fulfilled--;
        cnt[a[i - len]]--;
        cnt[a[i]]++;
        if (cnt[a[i]] == req[a[i]]) num_fulfilled++;

        if (num_fulfilled == r) return true;
    }
    return false;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k >> r;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, r) {
        int x;
        cin >> x >> req[x];
    }

    int l = 1, r = n;
    while (l != r) {
        int mid = (l + r) / 2;

        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    if (check(n)) cout << l << '\n';
    else cout << "impossible\n";
    return 0;
}