#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        ll g, h;
        cin >> g >> h;
        ll b = h;
        while (b <= g) b *= h;
        while (b % g) b++;
        cout << h * b + g << ' ' << b << '\n';
    }
    return 0;
}