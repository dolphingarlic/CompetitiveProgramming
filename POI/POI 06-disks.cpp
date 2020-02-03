#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, m, a[300001], pref_min[300001]{INT_MAX};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        pref_min[i] = min(a[i], pref_min[i - 1]);
    }
    
    n++;
    FOR(i, 0, m) {
        if (n) n--;
        int x;
        cin >> x;
        while (n && pref_min[n] < x) n--;
    }

    cout << n;
    return 0;
}