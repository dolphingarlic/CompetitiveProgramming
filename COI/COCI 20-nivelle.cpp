#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int active[26];
pair<int, int> mx[27];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;
    FOR(i, 1, 27) {
        mx[i] = {1, 0};
        int l = 0, colours = 0;
        fill(active, active + 26, 0);
        FOR(r, 0, n) {
            active[s[r] - 'a']++;
            if (active[s[r] - 'a'] == 1) colours++;
            while (colours > i) {
                active[s[l] - 'a']--;
                if (active[s[l] - 'a'] == 0) colours--;
                l++;
            }
            if (r - l > mx[i].second - mx[i].first) mx[i] = {l + 1, r + 1};
        }
    }

    long double mn = 1e18;
    pair<int, int> ans = {0, -1};
    FOR(i, 1, 27) {
        if ((long double)i / (mx[i].second - mx[i].first + 1) <= mn) {
            ans = mx[i];
            mn = (long double)i / (mx[i].second - mx[i].first + 1);
        }
    }
    cout << ans.first << ' ' << ans.second;
    return 0;
}