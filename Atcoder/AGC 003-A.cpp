#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    bool nn = false, ee = false, ww = false, ss = false;
    for (char c : s) {
        if (c == 'N') nn = true;
        if (c == 'E') ee = true;
        if (c == 'W') ww = true;
        if (c == 'S') ss = true;
    }
    cout << ((nn ^ ss) || (ee ^ ww) ? "No" : "Yes");
    return 0;
}
