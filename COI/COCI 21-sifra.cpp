#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    int curr = 0;
    set<int> ints;
    for (char c : s) {
        if (c >= '0' && c <= '9') curr = curr * 10 + c - '0';
        else {
            ints.insert(curr);
            curr = 0;
        }
    }
    ints.insert(curr);
    cout << ints.size() - 1;
    return 0;
}