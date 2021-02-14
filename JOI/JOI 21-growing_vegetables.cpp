/*
JOI 2021 Growing Vegetables is Fun
- Split the plants into prefix and suffix; they must be increasing and decreasing respectively
- Let's focus on the prefix: what's the minimum number of waterings to make it increasing?
- If we water plant i, then it's optimal also to water plant i + 1
- This means that the minimum cost is sum(max(0, a[i - 1] - a[i] + 1))
    - A similar formula holds for the suffix
- We can compute the prefix/suffix sums of these two formulae
- Furthermore, notice that we can water **across** the split
- Therefore, the answer is
    min(max(pref[i], suff[i + 1]) + (1 if such watering results in a[i] == a[i + 1]))
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll a[200002], pref[200002], suff[200002];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + max(0ll, a[i - 1] - a[i] + 1);
    for (int i = n; i; i--) suff[i] = suff[i + 1] + max(0ll, a[i + 1] - a[i] + 1);
    ll ans = LLONG_MAX;
    for (int i = 1; i < n; i++)
        ans = min(ans, max(pref[i], suff[i + 1]) + (a[i] + pref[i] == a[i + 1] + suff[i + 1]));
    cout << ans;
    return 0;
}