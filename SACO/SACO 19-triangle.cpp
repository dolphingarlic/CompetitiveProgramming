#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a, b, c;
    cin >> a >> b >> c;
    if (a + b + c != 180) return cout << "IMPOSSIBLE", 0;
    if (a == b && b == c) return cout << "EQUILATERAL", 0;
    if (a != b && b != c && c != a) return cout << "SCALENE", 0;
    cout << "ISOSCELES";
    return 0;
}