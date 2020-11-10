/*
CEOI 2018 Lottery
- Let dist(i, j) be the distance between a[i:i+l] and b[j:j+l]
- We can find dist(i + 1, j + 1) given dist(i, j) in O(1) time
    - This means we can find the answer to a query in O(N^2) time
- To get rid of the Q factor, we simply use prefix sums
- Complexity: O(N^2) with O(NQ) memory
*/

#include <bits/stdc++.h>
using namespace std;

int a[10000], lb[10001], pref[101][10000], ans[100][10000];
pair<int, int> k[100];

int main() {
    int n, l, q;
    scanf("%d %d", &n, &l);
    for (int i = 0; i < n; i++) scanf("%d", a + i);
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
        scanf("%d", &k[i].first);
        k[i].second = i;
    }
    sort(k, k + q);

    fill(lb, lb + l + 1, q);
    for (int t = q - 1; ~t; t--) {
        for (int i = 0; i <= l; i++) if (i <= k[t].first) lb[i] = t;
    }

    for (int dx = 1; dx <= n - l; dx++) {
        int diff = 0;
        for (int p = 0; p < l; p++) diff += (a[p] != a[dx + p]);
        pref[lb[diff]][0]++, pref[lb[diff]][dx]++;
        for (int i = 1; i <= n - l - dx; i++) {
            diff += (a[i + l - 1] != a[i + dx + l - 1]) - (a[i - 1] != a[i + dx - 1]);
            pref[lb[diff]][i]++, pref[lb[diff]][i + dx]++;
        }
    }
    for (int t = 0; t < q; t++) for (int i = 0; i <= n - l; i++) {
        if (t) pref[t][i] += pref[t - 1][i];
        ans[k[t].second][i] = pref[t][i];
    }
    for (int t = 0; t < q; t++) {
        for (int i = 0; i <= n - l; i++) printf("%d ", ans[t][i]);
        printf("\n");
    }
}