#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
        cout << (i * 2 - 1) % n + 1 << ' ' << i * 2 % n + 1 << '\n';
    return 0;
}
