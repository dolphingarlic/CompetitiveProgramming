#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        ll ax, ay, bx, by, cx, cy;
        cin >> ax >> ay >> bx >> by >> cx >> cy;
        ll prod = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
        if (prod > 0) cout << "LEFT\n";
        else if (prod < 0) cout << "RIGHT\n";
        else cout << "TOUCH\n";
    }
    return 0;
}