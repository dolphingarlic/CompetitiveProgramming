#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t, n;
    cin >> t >> n;
    while (t--) {
        for (int i = 1; i < n; i++) {
            cout << "M " << i << ' ' << n << endl;
            int pos;
            cin >> pos;
            if (pos != i) {
                cout << "S " << i << ' ' << pos << endl;
                bool g;
                cin >> g;
                assert(g);
            }
        }
        cout << "D" << endl;
        bool g;
        cin >> g;
        assert(g);
    }
    return 0;
}
