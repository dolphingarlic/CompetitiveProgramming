#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int a[10000];
vector<int> sequence = {23, 87, 56, 77};

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;

    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, n - sequence.size()) {
        int delta = a[i] - sequence[0];
        bool possible = true;
        FOR(j, 0, sequence.size()) if (a[i + j] - sequence[j] != delta) {
            possible = false;
            break;
        }
        if (possible) return cout << delta << '\n', 0;
    }

    // Shouldn't ever reach here
    assert(false);
    return 0;
}