#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[100000];

bool check(int max_wait, int n, int t) {
    int curr_start = a[0];
    bool possible = true;
    FOR(i, 1, n) {
        if (a[i] - curr_start > max_wait) {
            if (a[i - 1] + t - a[i] > max_wait) {
                possible = false;
                break;
            }
            curr_start = a[i];
        }
    }
    return possible;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, t;
    cin >> n >> t;
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n);

    int l = 0, r = 1e9;
    while (l != r) {
        int mid = (l + r) / 2;
        if (check(mid, n, t)) r = mid;
        else l = mid + 1;
    }

    cout << l;
    return 0;
}