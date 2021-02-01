#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void kmp(string s, int target) {
    int n = s.size(), ans = 0;
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        int j = p[i - 1];
        while (j && s[i] != s[j]) j = p[j - 1];
        if (s[i] == s[j]) j++;
        p[i] = j;
        if (p[i] == target) ans++;
    }
    cout << ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s, t;
    cin >> s >> t;
    kmp(t + "#" + s, t.size());
    return 0;
}
