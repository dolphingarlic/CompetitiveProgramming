/*
IZhO 2019 Bigger Segments
- dp[i] = {Maximum no. of segments for first i, Min sum of the last segment to get that maximum}
        = max(dp[j]) + 1 where pref[i] - pref[j] >= dp[j].second
- Notice how the optimal j is nondecreasing
- This means we can simply use a monotone deque to calculate dp
- Complexity: O(N)
*/

#include <stdio.h>

long pref[500001], dp_cost[500001];
int dp_cnt[500001], lptr, rptr, dq[500001];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%ld", pref + i);
        pref[i] += pref[i - 1];
        while (rptr - lptr && pref[i] - pref[dq[lptr + 1]] >= dp_cost[dq[lptr + 1]])
            ++lptr;
        dp_cnt[i] = dp_cnt[dq[lptr]] + 1;
        dp_cost[i] = pref[i] - pref[dq[lptr]];
        while (dp_cost[dq[rptr]] - dp_cost[i] >= pref[i] - pref[dq[rptr]])
            --rptr;
        dq[++rptr] = i;
    }
    printf("%d", dp_cnt[n]);
    return 0;
}