#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for (ll i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int a, b, ans = 0;
string g, s;

unordered_map<char, int> freq_target, freq_curr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> a >> b >> g >> s;
    
    for (char i = 'a'; i <= 'z'; i++) freq_curr[i] = freq_target[i] = 0;
    for (char i = 'A'; i <= 'Z'; i++) freq_curr[i] = freq_target[i] = 0;

    FOR(i, 0, a) freq_target[g[i]]++, freq_curr[s[i]]++;

    if (freq_curr == freq_target) ans++;

    FOR(i, a, b) {
        freq_curr[s[i]]++;
        freq_curr[s[i - a]]--;
        if (freq_curr == freq_target) ans++;
    }

    cout << ans << '\n';
    return 0;
}
