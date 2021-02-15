#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int cmp[100001], h[100002];
pair<int, int> vals[100001];

int find(int A) { return (A == cmp[A] ? A : cmp[A] = find(cmp[A])); }
void onion(int A, int B) { cmp[find(A)] = find(B); }

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    iota(cmp + 1, cmp + n + 1, 1);
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        vals[i] = {h[i], i};
    }
    sort(vals + 1, vals + n + 1, greater<pair<int, int>>());
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int curr = vals[i].first, j = i;
        if (!curr) break;
        vector<int> to_process = {vals[i].second};
        for (; j < n && vals[j + 1].first == curr; j++)
            to_process.push_back(vals[j + 1].second);
        for (int k : to_process) {
            if (h[k] <= h[k - 1]) onion(k, k - 1);
            if (h[k] <= h[k + 1]) onion(k, k + 1);
        }
        set<int> s;
        for (int k : to_process) s.insert(find(k));
        ans += s.size();
        i = j;
    }
    cout << ans;
    return 0;
}