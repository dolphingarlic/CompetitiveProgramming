#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    set<int> s;
    char c;
    cin >> c;
    while (c != 'x') {
        if (c == 'i') {
            int n;
            cin >> n;
            while (n--) {
                int x;
                cin >> x;
                s.insert(x);
            }
        } else if (c == 'r') {
            int n;
            cin >> n;
            while (n--) {
                int x;
                cin >> x;
                s.erase(x);
            }
        } else cout << *s.begin() << ' ' << *s.rbegin() << '\n';
        cin >> c;
    }
    return 0;
}
