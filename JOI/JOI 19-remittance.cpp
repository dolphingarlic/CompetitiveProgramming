/*
JOI 2019 Remittance
- Simulate the process and greedily pay people
- Complexity: O(N log MAX_A)
*/

#include <bits/stdc++.h>
using namespace std;

long long a[1000000], b[1000000];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lld %lld", a + i, b + i);
    if (!accumulate(b, b + n, 0)) return puts(accumulate(a, a + n, 0) ? "No" : "Yes"), 0;
    bool p = 1;
    while (p) {
        p = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > b[i]) {
                a[(i + 1) % n] += (a[i] - b[i] + 1) / 2;
                a[i] -= (a[i] - b[i] + 1) / 2 * 2;
                p = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) p |= (a[i] != b[i]);
    puts(p ? "No" : "Yes");
    return 0;
}