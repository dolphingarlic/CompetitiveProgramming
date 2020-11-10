#include <bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")
#pragma GCC target("sse4,avx2,fma,avx")
using namespace std;

int main() {
    int n, a[500], tot = 0;
    scanf("%d", &n);
    bitset<250001> base;
    base[0] = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
        tot += a[i];
        base |= base << a[i];
    }
    if ((tot & 1) || !base[tot >> 1]) return printf("0"), 0;

    bitset<250001> ans;
    for (int i = 1; i <= tot; i++) ans[i] = 1;

    for (int i = 0; i < n; i++) {
        bitset<250001> possible, good;
        possible[0] = 1;
        for (int j = 0; j < n; j++) if (j != i) possible |= possible << a[j];
        for (int j = tot - a[i] & 1; j <= tot - a[i]; j += 2) good[j] = possible[tot - a[i] - j >> 1];
        ans &= good;
    }

    printf("%d\n", ans.count());
    for (int i = 0; i <= tot; i++) if (ans[i]) printf("%d ", i);
    return 0;
}