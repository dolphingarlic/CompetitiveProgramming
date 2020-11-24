/*
JOI 2019 Examination
- The main idea is to use MO's algorithm
- Keep two pointers: one on S and one on T
- We can use an unordered map to check for students that satisfy both A and B
- Next, we can coordinate compress the sum of scores and then use a BIT to query
  the number of students satisfying A and B that also satisfy C
- Complexity: O(N (sqrt N + log N))
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int N = 100000, BCKT = 750;

int n, q;
int s[N], t[N], sums[N], sum_ptr[N];
pair<int, int> by_s[N], by_t[N];
vector<tuple<int, int, int, int>> queries[N / BCKT + 1];
int bit[N + 1];
int ans[N];

void update(int pos, int val) {
    for (; pos <= n; pos += pos & -pos) bit[pos] += val;
}

int query(int l, int r) {
    int ans = 0;
    for (; r; r -= r & -r) ans += bit[r];
    for (l--; l; l -= l & -l) ans -= bit[l];
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> t[i];
        sums[i] = s[i] + t[i];
        by_s[i] = {s[i], i};
        by_t[i] = {t[i], i};
    }
    sort(sums, sums + n);
    for (int i = 0; i < n; i++) {
        sum_ptr[i] = lower_bound(sums, sums + n, s[i] + t[i]) - sums + 1;
    }
    sort(by_s, by_s + n);
    sort(by_t, by_t + n);
    for (int i = 0; i < q; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a = lower_bound(by_s, by_s + n, make_pair(a, 0)) - by_s;
        b = lower_bound(by_t, by_t + n, make_pair(b, 0)) - by_t;
        c = lower_bound(sums, sums + n, c) - sums + 1;
        queries[a / BCKT].push_back(tuple<int, int, int, int>(a, b, c, i));
    }

    gp_hash_table<int, int> good_cnt;
    for (int i = N / BCKT, sptr = n, tptr = n; ~i; i--) {
        sort(queries[i].begin(), queries[i].end(), [](tuple<int, int, int, int> A, tuple<int, int, int, int> B) {
            return get<1>(A) > get<1>(B);
        });
        for (tuple<int, int, int, int> j : queries[i]) {
            int a, b, c, idx;
            tie(a, b, c, idx) = j;

            while (sptr > a) {
                good_cnt[by_s[sptr - 1].second]++;
                if (good_cnt[by_s[sptr - 1].second] == 2) {
                    update(sum_ptr[by_s[sptr - 1].second], 1);
                }
                sptr--;
            }
            while (sptr < a) {
                good_cnt[by_s[sptr].second]--;
                if (good_cnt[by_s[sptr].second] == 1) {
                    update(sum_ptr[by_s[sptr].second], -1);
                }
                sptr++;
            }
            while (tptr > b) {
                good_cnt[by_t[tptr - 1].second]++;
                if (good_cnt[by_t[tptr - 1].second] == 2) {
                    update(sum_ptr[by_t[tptr - 1].second], 1);
                }
                tptr--;
            }
            while (tptr < b) {
                good_cnt[by_t[tptr].second]--;
                if (good_cnt[by_t[tptr].second] == 1) {
                    update(sum_ptr[by_t[tptr].second], -1);
                }
                tptr++;
            }
            ans[idx] = query(c, n);
        }
    }

    for (int i = 0; i < q; i++) cout << ans[i] << '\n';
    return 0;
}