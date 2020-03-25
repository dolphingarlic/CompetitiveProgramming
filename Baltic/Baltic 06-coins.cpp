/*
Baltic 2006 Coin Collector
- Greedily take coins from least valuable to most valuable
- We take coin X iff (Sum of taken coins) + (X's value) < ((X + 1)'s value)
- This works because if we take X instead of some less valuable coin(s), either the number of coins take decreases
  (bad), or the sum of the taken coins increases (which could lead to future coins being unavailable)
- Complexity: O(N)
*/

#include <cstdio>

int a[500001], b[500001];

int main() {
    int n, k, sm = 0, cnt = 0;
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d %d", a + i, b + i);
    a[n] = k;
    for (int i = 0; i < n; i++) {
        if (b[i]) continue;
        if (sm + a[i] < a[i + 1]) sm += a[i], cnt++;
    }
    printf("%d\n%d\n", cnt, k - (sm ? sm : 1));
    return 0;
}