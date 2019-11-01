#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, fin, curr_x = 0, curr_lb = 0, curr_ub = 0;
    cin >> n >> fin;
    FOR(i, 0, n) {
        int x, a, b;
        cin >> x >> a >> b;
        a += 1 + ((abs(a + 1) & 1) ^ (x & 1)),
            b -= 1 + ((abs(b + 1) & 1) ^ (x & 1));

        curr_ub += (x - curr_x);
        curr_lb -= (x - curr_x);
        curr_x = x;
        curr_ub = min(curr_ub, b);
        curr_lb = max(curr_lb, a);
        if (curr_ub < curr_lb) return cout << "NIE\n", 0;
    }
    curr_lb -= (fin - curr_x);
    cout << (fin / 2) + curr_lb / 2 << '\n';
    return 0;
}