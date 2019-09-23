#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int bits[30];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    fill(bits, bits + 30, 2);
    FOR(i, 0, n) {
        string s;
        int t;
        cin >> s >> t;
        if (s == "AND") {
            FOR(j, 0, 30) {
                if ((t & 1) == 0) bits[j] = 0;
                t >>= 1;
            }
        } else if (s == "OR") {
            FOR(j, 0, 30) {
                if ((t & 1) == 1) bits[j] = 1;
                t >>= 1;
            }
        } else {
            FOR(j, 0, 30) {
                if ((t & 1) == 1) bits[j] = 1 - bits[j];
                t >>= 1;
            }
        }
    }

    int res = 0, curr = 0;
    for (int i = 29; ~i; i--) {
        if (bits[i] == 1 || bits[i] == -1) res += (1<<i);
        else if (bits[i] == 2 && curr + (1<<i) <= m) {
            res += (1<<i), curr += (1<<i);
        }
    }

    cout << res;
    return 0;
}