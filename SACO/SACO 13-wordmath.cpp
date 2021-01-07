#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int map_to[26];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string a, b, c;
    cin >> a >> b >> c;
    int n = max({a.size(), b.size(), c.size()});
    set<char> charset;
    for (char i : a) charset.insert(i);
    for (char i : b) charset.insert(i);
    for (char i : c) charset.insert(i);
    if (charset.size() > 10) return cout << 0, 0;

    vector<int> perm(10);
    iota(perm.begin(), perm.end(), 0);
    int ans = 0;
    do {
        int i;
        bool good = true;
        for (i = charset.size() + 1; i < 10 && good; i++) good &= (perm[i] > perm[i - 1]);
        if (!good) continue;

        i = 0;
        for (char c : charset) map_to[c - 'A'] = perm[i++];
        if (!map_to[a[0] - 'A'] || !map_to[b[0] - 'A'] || !map_to[c[0] - 'A'])
            continue;
        int carry = 0;
        for (i = 1; i <= n && good; i++) {
            int da = (i > a.size() ? 0 : map_to[a[a.size() - i] - 'A']);
            int db = (i > b.size() ? 0 : map_to[b[b.size() - i] - 'A']);
            int dc = (i > c.size() ? 0 : map_to[c[c.size() - i] - 'A']);
            good &= !(da + db + carry - dc) || da + db + carry - dc == 10;
            carry = da + db + carry > 9;
        }
        ans += good && !carry;
    } while (next_permutation(perm.begin(), perm.end()));
    cout << ans;
    return 0;
}