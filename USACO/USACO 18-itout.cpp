/*
USACO 2018 Sort It Out
- Firstly, notice that the relative order of the cows outside the chosen set remains the same
- Next, notice that if the cows outside the chosen set form an increasing sequence, then the
  cows will always become sorted
    - This is because if 2 cows in the chosen set are out of order, they will always swap at some point
- This means that the size of the smallest chosen set is N - (LIS of all cows)
- To get the K-th lexographically smallest chosen set, we find the K-th lexographically largest LIS
- Let dp[i] = Number of "local" LIS's starting on cow i (i.e. LIS's that must have cow i as its first cow)
- If we want the x-th cow of our LIS, process all i with "local" LIS length = (LIS of all cows) - x in
  increasing order of ID
    - If dp[i] >= K, then we take element i
    - Otherwise, subtract dp[i] from K and continue
    - Also make sure that we never take an element before a previously taken element
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, a[100001], len[100001], lis[100001], mn = 0;
ll k, num[100001], dp[100001];
vector<int> has_len[100001];

void update(int pos, int ln, ll nm) {
    for (; pos <= n; pos += pos & (-pos)) {
        if (len[pos] == ln) num[pos] = min(k + 1, num[pos] + nm);
        else if (len[pos] < ln) num[pos] = nm, len[pos] = ln;
    }
}

pair<int, ll> query(int pos) {
    pair<int, ll> ans;
    for (; pos; pos -= pos & (-pos)) {
        if (len[pos] == ans.first) ans.second = min(k + 1, ans.second + num[pos]);
        else if (len[pos] > ans.first) ans = {len[pos], num[pos]};
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ifstream cin("itout.in");
    ofstream cout("itout.out");
    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = n; i; i--) {
        tie(lis[i], dp[i]) = query(n + 1 - a[i]);
        if (!lis[i]) dp[i]++;
        has_len[++lis[i]].push_back(i);
        mn = max(mn, lis[i]);
        update(n + 1 - a[i], lis[i], dp[i]);
    }

    set<int> s;
    for (int i = 1; i <= n; i++) s.insert(i);

    cout << n - mn << '\n';
    for (int i = mn, prv = 0; i; i--) {
        sort(has_len[i].begin(), has_len[i].end(), [](int A, int B) { return a[A] > a[B]; });
        for (int j : has_len[i]) {
            if (j < prv) continue;
            if (dp[j] >= k) {
                s.erase(a[j]);
                prv = j;
                break;
            } else k -= dp[j];
        }
    }
    for (int i : s) cout << i << '\n';
    return 0;
}