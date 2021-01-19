/*
SACO 2021 Smallest Concatenation
- Custom sort: A < B -> A + B < B + A
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

bool cmp(string a, string b) {
    string s1 = a + b, s2 = b + a;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] < s2[i]) return true;
        if (s2[i] < s1[i]) return false;
    }
    return false;
}

string s[50000];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i];
    sort(s, s + n, cmp);
    for (int i = 0; i < n; i++) cout << s[i];
    return 0;
}
