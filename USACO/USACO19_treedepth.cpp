#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k;
ll m;
int perm[20];
ll ans[20];

int main() {
    freopen("treedepth.in", "r", stdin);
    freopen("treedepth.out", "w", stdout);
    cin >> n >> k >> m;
    iota(perm, perm + n, 1);
    do {
        int invs = 0;
        for (int i = 0; i < n; i++) for (int j = 0; j < i; j++)
            invs += (perm[j] > perm[i]);
        if (invs != k) continue;
        for (int i = 0; i < n; i++) {
            ans[i]++;
            for (int j = i - 1, mn = perm[i]; ~j; j--) {
                mn = min(mn, perm[j]);
                ans[i] += mn == perm[j];
            }
            for (int j = i + 1, mn = perm[i]; j < n; j++) {
                mn = min(mn, perm[j]);
                ans[i] += mn == perm[j];
            }
            ans[i] %= m;
        }
    } while (next_permutation(perm, perm + n));
    for (int i = 0; i < n; i++) cout << ans[i] << " \n"[i == n - 1];
    return 0;
}