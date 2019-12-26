#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    FOR(i, 0, 100000) cout << 'a';
    cout << "\n100000\n";
    FOR(i, 0, 100000) cout << "1 1\n";
    FOR(i, 0, 100000) cout << i + 1 << ' ';
    return 0;
}