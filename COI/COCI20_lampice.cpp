#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int P[100001];
string insertHashes(string s) {
    string newString = "@";
    for (int i = 0; i < s.size(); i++) newString += "#" + s.substr(i, 1);
    newString += "#$";
    return newString;
}
int manacher(string s) {
    string Q = insertHashes(s);
    int c = 0, r = 0;
    for (int i = 1; i < Q.size() - 1; i++) {
        int iMirror = c - (i - c);
        if (r > i) P[i] = min(r - i, P[iMirror]);
        while (Q[i + 1 + P[i]] == Q[i - 1 - P[i]]) P[i]++;
        if (i + P[i] > r) {
            c = i;
            r = i + P[i];
        }
    }

    int maxPalindrome = 0;
    int centerIndex = 0;
    for (int i = 1; i < Q.size() - 1; i++) {
        if (P[i] > maxPalindrome) {
            maxPalindrome = P[i];
            centerIndex = i;
        }
    }
    return maxPalindrome;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    string s;
    cin >> n >> s;
    cout << manacher(s);
    return 0;
}