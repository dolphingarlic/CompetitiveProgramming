#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n, s, t;
    cin >> n >> s >> t;
    cout << (n - 1) * t + (int)ceil(log2(n)) * s << '\n' << (n + 1) / 2;
    return 0;
}