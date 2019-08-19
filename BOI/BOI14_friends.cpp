#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    if (!(n & 1)) return cout << "NOT POSSIBLE\n", 0;
    string s;
    cin >> s;
    
    string a = s.substr(0, n / 2), b = s.substr(n / 2 + 1, n / 2);
    if (a == b) return cout << a << '\n', 0;
 
    bool a_possible = true, b_possible = true;
    
    bool chucked = false;
    ll pos = 0;
    FOR(i, n / 2, n) {
        if (a[pos] == s[i]) pos++;
        else if (!chucked) chucked = true;
        else {
            a_possible = false;
            break;
        }
    }
    chucked = false;
    pos = 0;
    FOR(i, 0, n / 2 + 1) {
        if (b[pos] == s[i]) pos++;
        else if (!chucked) chucked = true;
        else {
            b_possible = false;
            break;
        }
    }
 
    if (a_possible && b_possible) cout << "NOT UNIQUE\n";
    else if (a_possible) cout << a << '\n';
    else if (b_possible) cout << b << '\n';
    else cout << "NOT POSSIBLE\n";
    return 0;
}