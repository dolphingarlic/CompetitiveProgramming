#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    int n, x, y;
    scanf("%d %d %d", n, x, y);

    bool fits = true;
    int len = 1;
    for (; fits && x + len <= n; len <<= 1) {
        printf("examine %d %d", x + len, y);
        scanf("%b", &fits);
    }
    len >>= 1;
    int l = 0, r = len;
    return 0;
}