// Basically we want Bytesar to start on the computer with
// the maximum of the minimums of semicircle sums that contain
// that computer, since the operator is able to force him to do that

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1000050;

int a[N];
ll sum[N], p[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) cin >> a[i], a[i + n] = a[i];
    for (int i = 1; i <= n * 2; i++) sum[i] = sum[i - 1] + a[i]; // Prefix sums

    int sz = (n + 1) / 2;

    // Sums of semicircles
    for (int i = 1; i <= n; i++) p[i] = sum[i + sz - 1] - sum[i - 1];
    for (int i = n + 1; i <= n * 2; i++) p[i] = p[i - n];

    // Monotonic queue - Easily get min in range
    deque<int> dq;
    for (int i = n - sz + 2; i <= n; i++) {
        while (dq.size() && p[dq.back()] >= p[i]) dq.pop_back();
        dq.push_back(i);
    }

    ll ans = 0;

    for (int i = n + 1; i <= 2 * n; i++) {
        while (dq.size() && p[dq.back()] >= p[i]) dq.pop_back();
        dq.push_back(i);
        // Make sure we only consider semicircle sums that contain
        // the current computer i
        while (dq.front() < i - sz + 1) dq.pop_front();
        ans = max(ans, p[dq.front()]);
    }

    cout << ans << '\n';
    return 0;
}