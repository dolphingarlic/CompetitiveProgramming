#include <math.h>
#include <algorithm>
#include <iostream>
using namespace std;

int n;
int A[1000002], D[2000002];

int maximum() {
    int ret = 0;
    for (int i = 0; i < n; i++) D[i + n] = D[i];

    for (int i = 2 * n - 1; i >= 0; i--) {
        if (!D[i])
            D[i] = D[i + 1] + 1;
        else
            D[i] = 0;
        ret = max(ret, D[i]);
    }

    if (n % 2 == 0) return (n / 2) - (ret + 1) / 2;
    return (n / 2) - ret / 2;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) cin >> A[i];

    int i, a, b, c, lim = (n - 1) / 2;
    for (i = 1; i <= n; i++) {
        a = i >= A[i] ? i - A[i] : n - A[i] + i;
        b = -(A[i] >= i ? A[i] - i : n - i + A[i]);
        c = abs(a) <= abs(b) ? a : b;
        D[c + lim] = 1;
    }
    int ans = maximum();

    fill(D, D + 2 * n + 1, 0);
    reverse(A + 2, A + n + 1);
    for (i = 1; i <= n; i++) {
        a = i >= A[i] ? i - A[i] : n - A[i] + i;
        b = -(A[i] >= i ? A[i] - i : n - i + A[i]);
        c = abs(a) <= abs(b) ? a : b;
        D[c + lim] = 1;
    }
    ans = min(ans, maximum());
    cout << ans << "\n";
}