#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll P1 = 9973, P2 = 69420, M1 = 1e9 + 9, M2 = 998244353;

int freq_target[26], freq_curr[26];
string s, t;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> s >> t;
    if (s.size() > t.size()) return cout << 0, 0;

    set<pair<ll, ll>> good;
    ll poly1 = 0, poly2 = 0, p_pow1 = 1, p_pow2 = 1;
    for (int i = 0; i < s.size(); i++) {
        freq_target[s[i] - 'a']++, freq_curr[t[i] - 'a']++;
        poly1 = (poly1 * P1 + (t[i] - 'a')) % M1;
        poly2 = (poly2 * P2 + (t[i] - 'a')) % M2;
        p_pow1 = p_pow1 * P1 % M1;
        p_pow2 = p_pow2 * P2 % M2;
    }
    {
        bool match = true;
        for (int j = 0; j < 26; j++) match &= freq_curr[j] == freq_target[j];
        if (match) good.insert({poly1, poly2});
    }

    for (int i = s.size(); i < t.size(); i++) {
        freq_curr[t[i] - 'a']++;
        freq_curr[t[i - s.size()] - 'a']--;
        poly1 = (poly1 * P1 - p_pow1 * (t[i - s.size()] - 'a') % M1 + (t[i] - 'a') + M1) % M1;
        poly2 = (poly2 * P2 - p_pow2 * (t[i - s.size()] - 'a') % M2 + (t[i] - 'a') + M2) % M2;
        
        bool match = true;
        for (int j = 0; j < 26; j++) match &= freq_curr[j] == freq_target[j];
        if (match) good.insert({poly1, poly2});
    }

    cout << good.size() << '\n';
    return 0;
}
