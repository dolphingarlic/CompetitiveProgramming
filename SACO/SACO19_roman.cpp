#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

map<char, ll> ord = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
vector<map<ll, string>> digit =  {
    {{0, ""}, {1, "I"}, {2, "II"}, {3, "III"}, {4, "IV"}, {5, "V"}, {6, "VI"}, {7, "VII"}, {8, "VIII"}, {9, "IX"}},
    {{0, ""}, {1, "X"}, {2, "XX"}, {3, "XXX"}, {4, "XL"}, {5, "L"}, {6, "LX"}, {7, "LXX"}, {8, "LXXX"}, {9, "XC"}},
    {{0, ""}, {1, "C"}, {2, "CC"}, {3, "CCC"}, {4, "CD"}, {5, "D"}, {6, "DC"}, {7, "DCC"}, {8, "DCCC"}, {9, "CM"}},
    {{0, ""}, {1, "M"}, {2, "MM"}, {3, "MMM"}}
};

ll to_arabic(string rom) {
    ll res = 0;
    FOR(i, 0, rom.size()) {
        if (i != rom.size() - 1 && ord[rom[i]] < ord[rom[i + 1]]) {
            res += ord[rom[i + 1]] - ord[rom[i]];
            i++;
        } else res += ord[rom[i]];
    }
    return res;
}
string to_roman(ll arab) {
    string res = "";

    for (ll i = 0; arab; i++) {
        string add = digit[i][arab % 10];
        reverse(add.begin(), add.end());
        res += add;
        arab /= 10;
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    string a, b;
    cin >> a >> b;

    cout << to_roman(to_arabic(a) + to_arabic(b));
    return 0;
}