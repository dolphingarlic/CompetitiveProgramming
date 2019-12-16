#include <bits/stdc++.h>
using namespace std;

int findSample(int n, int c[], int h[], int p[]) {
    int ans = 0;
    for (int i = n - 1; i > 0; i--) {
        if (p[i] == 0) ans += c[i], c[h[i]] = max(0, c[h[i]] - c[i]);
        if (p[i] == 1) c[h[i]] += c[i];
        if (p[i] == 2) c[h[i]] = max(c[h[i]], c[i]);
    }
    return ans + c[0];
}