#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

vector<string> solve(int len) {
    if (len == 1) return {"0", "1"};
    vector<string> fwd = solve(len - 1);
    vector<string> rev = fwd; reverse(rev.begin(), rev.end());
    for (int i = 0; i < (1 << len - 1); i++) {
        fwd[i] = "0" + fwd[i];
        rev[i] = "1" + rev[i];
    }
    fwd.insert(fwd.end(), rev.begin(), rev.end());
    return fwd;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<string> ans = solve(n);
    for (string i : ans) cout << i << '\n';
    return 0;
}