#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

ll a[100][100];
map<ll, ll> freq;

bool ismagic(ll n) {
    ll target = 0;
    FOR(i, 0, n) target += a[i][0];

    FOR(i, 0, n) {
        ll row_sum = 0, col_sum = 0;
        FOR(j, 0, n) {
            row_sum += a[i][j];
            col_sum += a[j][i];
        }
        if (row_sum != target || col_sum != target) return false;
    }
    return true;
}

void get_freq(ll n) {
    ll target = 0;
    FOR(i, 0, n) target += a[i][0];

    FOR(i, 0, n) {
        ll row_sum = 0, col_sum = 0;
        FOR(j, 0, n) {
            row_sum += a[i][j];
            col_sum += a[j][i];
        }
        freq[row_sum]++;
        freq[col_sum]++;
    }
}
bool check() {
    vector<int> v;
    for (pair<int, int> i : freq) v.push_back(i.second);
    sort(v.begin(), v.end());
    return (v.size() == 2 && v[0] == 2);
}

pair<pair<ll, ll>, ll> get_tochange(ll n, ll target) {
    pair<ll, ll> res;
    ll diff;

    FOR(i, 0, n) {
        ll row_sum = 0, col_sum = 0;
        FOR(j, 0, n) {
            row_sum += a[i][j];
            col_sum += a[j][i];
        }
        if (row_sum != target) {
            res.first = i + 1;
            diff = row_sum - target;
        }
        if (col_sum != target) res.second = i + 1;
    }
    return {res, a[res.first - 1][res.second - 1] - diff};
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    ll n;
    cin >> n;
    FOR(i, 0, n) FOR(j, 0, n) cin >> a[i][j];

    if (ismagic(n)) cout << "MAGIC";
    else {
        get_freq(n);
        if (check()) {
            cout << "ALMOST MAGIC\n";
            ll target_cnt = 0, target = 0;
            for (pair<ll, ll> i : freq) if (i.second > target_cnt) {
                target = i.first;
                target_cnt = i.second;
            }

            pair<pair<ll, ll>, ll> tochange = get_tochange(n, target);
            cout << tochange.first.first << ' ' << tochange.first.second << ' ' << tochange.second;
        } else {
            cout << "NOT MAGIC";
        }
    }
    return 0;
}