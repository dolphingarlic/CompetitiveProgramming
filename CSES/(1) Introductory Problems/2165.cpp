#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void solve(int sz, int src, int dest) {
    if (!sz) return;
    solve(sz - 1, src, 6 - src - dest);
    cout << src << ' ' << dest << '\n';
    solve(sz - 1, 6 - src - dest, dest);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    cout << (1 << n) - 1 << '\n';
    solve(n, 1, 3);
    return 0;
}