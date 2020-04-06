#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    string t = s;
    sort(t.begin(), t.end());
    if (t == s) cout << "True";
    else cout << "False";
    return 0;
}