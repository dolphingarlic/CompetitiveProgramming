/*
SACO 2020 Count Special
- Answer = N / A + N / B - N / lcm(A, B) because PIE
- Complexity: O(log(max(A, B)))
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a, b, n;
    cin >> a >> b >> n;
    n--;
    cout << n / a + n / b - n / ((a * b) / __gcd(a, b));
    return 0;
}