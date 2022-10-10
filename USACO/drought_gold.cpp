#include <algorithm>
#include <cstdio>
#include <numeric>
using namespace std;

int mod_add(int x, int y) {
    int res = x + y;
    if (res >= 1000000007) res -= 1000000007;
    return res;
}

int main() {
    int n, h[101], mn, mx, dp[1001], ans = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d", h + i);
    mn = *min_element(h, h + n), mx = *max_element(h, h + n);
    do {
        fill(dp, dp + mx + 1, 1);
        for (int i = 0; i < n; i++) {
            reverse(dp, dp + h[i] + 1);
            fill(dp + h[i] + 1, dp + mx + 1, 0);
            partial_sum(dp, dp + mx + 1, dp, mod_add);
        }
        ans = mod_add(ans, dp[0]);
        for (int i = 0; i < n; i++) h[i]--;
    } while (n % 2 && mn-- && mx--);
    printf("%d\n", ans);
    return 0;
}
