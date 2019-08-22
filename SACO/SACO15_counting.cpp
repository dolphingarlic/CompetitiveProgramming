#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

vector<char> chars;
map<char, int> cnt;

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    for (char i : s) {
        cnt[i]++;
        if (cnt[i] == 1) chars.push_back(i);
    }
    for (char i : chars) cout << i << cnt[i];
    return 0;
}