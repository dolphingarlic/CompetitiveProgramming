/*
SACO 2020 All about that Base
- Just add the numbers
- Complexity: O(Size of input)
*/

#include <bits/stdc++.h>
using namespace std;

map<char, int> dig;
map<int, char> chr;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int b;
    string x, y;
    cin >> b >> x >> y;
    for (int i = 0, c = '0'; i < min(10, b); i++, c++) dig[c] = i, chr[i] = c;
    for (int i = 10, c = 'A'; i < b; i++, c++) dig[c] = i, chr[i] = c;
    while (x.size() < y.size()) x = '0' + x;
    while (y.size() < x.size()) y = '0' + y;
    string ans = "";
    bool carry = false;
    for (int i = x.size() - 1; ~i; i--) {
        int nw = dig[x[i]] + dig[y[i]] + carry;
        carry = false;
        if (nw >= b) {
            carry = true;
            nw -= b;
        }
        ans = chr[nw] + ans;
    }
    if (carry) ans = '1' + ans;
    cout << ans;
    return 0;
}