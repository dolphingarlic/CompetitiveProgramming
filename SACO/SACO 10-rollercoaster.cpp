#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
using namespace std;

int component[102];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int k, n;
    cin >> k >> n;

    FOR(i, 1, k + 2) component[i] = i;

    FOR(i, 1, n + 1) {
        int x;
        cin >> x;
        while (component[x] != x) {
            component[x] = component[component[x]];
            x = component[x];
        }

        if (x <= k) component[x]++;
        else cout << i << '\n';
    }

    return 0;
}