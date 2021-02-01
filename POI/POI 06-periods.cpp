/*
POI 2006 Periods of Words
- Notice how a string T has a period iff it has a proper prefix that is also a suffix
    - Moreover, the maximal period length is |T| - |Shortest such prefix|
- Let's compute the prefix function of the given string S (like KMP)
- We can then find the shortest good prefixes by continuing to reduce p[i] until just
  before it reaches 0 -- this will be the shortest length
- See implementation for more details
- Complexity: O(N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int p[1000000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    string s;
    cin >> n >> s;
    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        if (!p[i]) continue;
        while (p[p[i] - 1]) p[i] = p[p[i] - 1];
        ans += i + 1 - p[i];
    }
    cout << ans;
    return 0;
}
