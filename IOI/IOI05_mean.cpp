#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
using namespace std;

int n;
long long l = INT_MAX, r = INT_MIN;
long long ant, act;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> act;
        act *= 2;
        act -= ant;
        if (i % 2)
            l = min(l, (act - ant) / 2);
        else
            r = max(r, (ant - act) / 2);
        ant = act;
    }
    if (r <= l)
        cout << l - r + 1 << "\n";
    else
        cout << 0 << "\n";

    return 0;
}