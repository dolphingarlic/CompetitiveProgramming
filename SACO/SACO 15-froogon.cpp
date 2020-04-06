#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> res;
    for (int i = 1; n; i++) {
        res.push_back(n % (i + 1));
        n /= i + 1;
    }

    for (int i : res) cout << i << ' ';
    return 0;
}