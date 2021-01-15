#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, x;
    multiset<int> s;
    cin >> n >> x;
    FOR(i, 0, n) {
        int v;
        cin >> v;
        s.insert(v);
    }
 
    int cnt = 0;
    for (; s.size(); cnt++) {
        int v = *s.rbegin();
        s.erase(s.find(v));
        if (s.upper_bound(x - v) != s.begin()) s.erase(prev(s.upper_bound(x - v)));
    }
    cout << cnt;
    return 0;
}