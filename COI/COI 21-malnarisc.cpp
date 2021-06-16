/*
COI 2021 MalnaRISC
- This is a nerfed version of Baltic '21 Swaps, so see that solution too
- https://en.wikipedia.org/wiki/Bitonic_sorter
- https://en.wikipedia.org/wiki/Batcher_odd%E2%80%93even_mergesort
- O(log^2 N) steps to sort in parallel
*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int p2 = 1, blocks = 0;
    while (p2 < n) p2 <<= 1, blocks++;
    printf("%d\n", blocks * (blocks + 1) / 2);
    for (int p = 1; p < p2; p <<= 1)
        for (int k = p; k; k >>= 1) {
            for (int j = k % p; j < p2 - k; j += 2 * k)
                for (int i = 0; i < k && i + j + k < n; i++)
                    if ((i + j) / (2 * p) == (i + j + k) / (2 * p))
                        printf("CMPSWP R%d R%d ", i + j + 1, i + j + k + 1);
            printf("\n");
        }
    return 0;
}
