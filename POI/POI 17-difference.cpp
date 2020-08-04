/*
POI 2017 Difference Representations
- Consider the consecutive differences in the sequence
    - Notice how they grow almost exponentially, so there will only be ~60
      elements in the sequence before some consecutive difference exceeds 1e9
    - This means we can just find those first ~60 elements with brute force
- We have 2 cases
    - Case 1: Both indices of repr(x) are less than ~60 
        - Just do it
    - Case 2: Both indices of repr(x) are greater than ~60
        - Since a[2k + 1] - a[2k] > 1e9 for each k > 30, we can just
          work out the indices of repr(x) directly, since they
          must be consecutive
- Complexity: O(N log 1e9)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (ll i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MX = 1e9;

vector<ll> seq = {1, 2};
map<ll, pair<int, int>> r = {{1, {2, 1}}};
ll in_r[1600], mn_r, cnt;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    while (true) {
        if (seq.size() & 1) {
            FOR(i, 1, MX) if (!r[i].first) {
                seq.push_back(seq.back() + i);
                break;
            }
        } else {
            seq.push_back(seq.back() << 1);
            if ((seq.back() >> 1) > MX) break;
        }
        FOR(i, 0, seq.size() - 1) {
            r[seq.back() - seq[i]] = {seq.size(), i + 1};
        }
    }

    for (pair<ll, pair<int, int>> i : r) in_r[cnt++] = i.first;
    FOR(i, 1, MX) if (!r[i].first) {
        mn_r = i;
        break;
    }

    int n;
    cin >> n;
    while (n--) {
        ll x;
        cin >> x;
        if (r[x].first) {
            cout << r[x].first << ' ' << r[x].second << '\n';
        } else {
            ll idx = seq.size() + 2 * (x - mn_r +
                                       ll(lower_bound(in_r, in_r + cnt, mn_r) -
                                          lower_bound(in_r, in_r + cnt, x)));
            cout << idx + 1 << ' ' << idx << '\n';
        }
    }
    return 0;
}