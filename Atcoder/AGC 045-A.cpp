#include <array>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

ll a[200], basis[60];

bool in_span(ll val) {
    for (int i = 59; ~i; i--)
        if (val & (1ll << i)) val ^= basis[i];
    return val == 0;
}

void add_vec(ll val) {
    for (int i = 59; ~i; i--)
        if (val & (1ll << i))
            if (basis[i]) val ^= basis[i];
            else {
                basis[i] = val;
                return;
            }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) cin >> a[i];
        string s;
        cin >> s;
        memset(basis, 0, sizeof basis);
        bool win = true;
        for (int i = n - 1; ~i && win; i--) {
            if (!in_span(a[i])) {
                if (s[i] == '0')
                    add_vec(a[i]);
                else
                    win = false;
            }
        }
        cout << "10"[win] << '\n';
    }
}
