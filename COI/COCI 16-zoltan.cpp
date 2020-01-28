/*
COCI 2016 Zoltan
- https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2017/contest3_solutions
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

int n, a[200001], g_len[200001];
ll pw[200001], g_num[200001];
vector<int> uniq;
pair<int, ll> lis[200001], lds[200001];
map<int, int> mp;

void update(int pos, int len, ll num) {
    for (; pos < n; pos += (pos & (-pos))) {
        if (g_len[pos] == len) {
            g_num[pos] = (g_num[pos] + num) % MOD;
        } else if (g_len[pos] < len) {
            g_len[pos] = len;
            g_num[pos] = num;
        }
    }
}
pair<int, ll> query(int pos) {
    pair<int, ll> ans;
    for (; pos; pos -= (pos & (-pos))) {
        if (g_len[pos] == ans.first) {
            ans.second = (ans.second + g_num[pos]) % MOD;
        } else if (g_len[pos] > ans.first) {
            ans = {g_len[pos], g_num[pos]};
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    pw[0] = 1;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        pw[i] = (pw[i - 1] * 2) % MOD;
        uniq.push_back(a[i]);
    }
    sort(uniq.begin(), uniq.end());
    uniq.erase(unique(uniq.begin(), uniq.end()), uniq.end());
    FOR(i, 0, uniq.size()) mp[uniq[i]] = i + 1;
    FOR(i, 1, n + 1) a[i] = mp[a[i]];
    reverse(a + 1, a + n + 1);

    FOR(i, 1, n + 1) {
        int len;
        ll num;
        tie(len, num) = query(a[i]);
        if (!len) num = 1;
        len++;
        lis[i] = {len, num};
        update(a[i] + 1, len, num);
    }
    FOR(i, 0, n + 1) a[i] = n - a[i], g_num[i] = g_len[i] = 0;
    FOR(i, 1, n + 1) {
        int len;
        ll num;
        tie(len, num) = query(a[i]);
        if (!len) num = 1;
        len++;
        lds[i] = {len, num};
        update(a[i] + 1, len, num);
    }

    int ans = -1;
    ll a_num = -1;
    FOR(i, 1, n + 1) {
        int len = lis[i].first + lds[i].first - 1;
        ll num = (pw[n - len] * (lis[i].second * lds[i].second) % MOD) % MOD;
        if (len == ans) {
            a_num = (a_num + num) % MOD;
        } else if (len > ans) {
            ans = len;
            a_num = num;
        }
    }
    cout << ans << ' ' << a_num;
    return 0;
}