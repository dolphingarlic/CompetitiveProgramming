#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int b[100001];
set<int> s;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, curr;
    cin >> n;
    FOR(i, 1, n + 1) {
        cin >> b[i];
        s.insert(2 * i - 1);
        s.insert(2 * i);
    }
    s.erase(2 * n);

    cout << b[1] << ' ';
    s.erase(b[1]);
    FOR(i, 2, n + 1) {
        if (b[i] == b[i - 1]) {
            cout << *s.begin() << ' ';
            s.erase(*s.begin());
            cout << *s.rbegin() << ' ';
            s.erase(*s.rbegin());
        } else if (b[i] > b[i - 1]) {
            if (s.find(b[i]) == s.end()) {
                cout << *s.rbegin() << ' ';
                s.erase(*s.rbegin());
                cout << *s.rbegin() << ' ';
                s.erase(*s.rbegin());
            } else {
                cout << b[i] << ' ';
                s.erase(b[i]);
                cout << *s.rbegin() << ' ';
                s.erase(*s.rbegin());
            }
        } else {
            if (s.find(b[i]) == s.end()) {
                cout << *s.begin() << ' ';
                s.erase(*s.begin());
                cout << *s.begin() << ' ';
                s.erase(*s.begin());
            } else {
                cout << b[i] << ' ';
                s.erase(b[i]);
                cout << *s.begin() << ' ';
                s.erase(*s.begin());
            }
        }
    }
    return 0;
}