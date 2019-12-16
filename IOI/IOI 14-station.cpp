#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int a[500001];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> a[i];

    queue<int> window;
    int days = 0, curr = 0;
    FOR(i, 1, k + 1) if (a[i]) window.push(i);
    while (!window.empty()) {
        curr = window.back();
        while (!window.empty()) window.pop();
        FOR(i, curr + 1, min(n, curr + k + 1)) if (a[i]) window.push(i);
        days++;
    }
    if (curr == n - 1) cout << days;
    else cout << "-1\n";
    return 0;
}