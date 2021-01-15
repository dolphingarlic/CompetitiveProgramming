#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll sep[18]{0ll, 9ll * 1, 90ll * 2, 900ll * 3, 9000ll * 4, 90000ll * 5, 900000ll * 6, 9000000ll * 7,
                 90000000ll * 8, 900000000ll * 9, 9000000000ll * 10,  90000000000ll * 11, 900000000000ll * 12,
                 9000000000000ll * 13, 90000000000000ll * 14, 900000000000000ll * 15,
                 9000000000000000ll * 16, 90000000000000000ll * 17};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        ll strt = 1;
        for (int i = 1; i <= 17; i++, strt *= 10) {
            if (k <= sep[i]) {
                cout << to_string(strt + (k - 1) / i)[(k - 1) % i] << '\n';
                break;
            } else k -= sep[i];
        }
    }
    return 0;
}