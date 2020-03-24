#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (long long i = x; i < y; i++)
#define MOD 1000000007
using namespace std;

long long calc(long long val, long long n) {
    long long bit_cnt = 0, ans = 0;
    bool is_one = false;

    int lrg;
    for (int i = 31; ~i; i--) if ((n - 1) & (1 << i)) {
        lrg = (1 << i);
        break;
    }
    if (val & lrg) {
        ans++;
        val -= lrg;
    }

    for (long long i = 0; val > 0; i++) {
        if ((val & (1 << i)) != 0) {
            is_one = true;
            bit_cnt++;
        } else if (is_one) {
            if (bit_cnt == 1) {
                ans += bit_cnt;
                is_one = false;
                bit_cnt = 0;
                val >>= i; val <<= i;
            } else {
                ans++;
                bit_cnt = 1;
                bit_cnt = 1;
                val >>= i; val++; val <<= i;
            }
        }
    }

    return ans;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    long long n, m;
    cin >> n >> m;
    long long val = 0;
    FOR(i, 0, n) val += calc(i, n);
    cout << val * 3 * n * n << '\n';
    FOR(i, 0, m) {
        long long a, b, c;
        cin >> a >> b >> c;
        cout << calc(a - 1, n) + calc(b - 1, n) + calc(c - 1, n) << '\n';
    }
    return 0;
}