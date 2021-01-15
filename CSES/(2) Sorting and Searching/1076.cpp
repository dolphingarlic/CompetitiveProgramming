#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
int a[200001];
multiset<int> l, r;
 
void insert(int val) {
    int median = (l.size() ? *l.rbegin() : INT_MAX);
    if (val > median) r.insert(val);
    else l.insert(val);
 
    if (r.size() > l.size()) {
        l.insert(*r.begin());
        r.erase(r.begin());
    } else if (l.size() > r.size() + 1) {
        r.insert(*l.rbegin());
        l.erase(prev(l.end()));
    }
}
 
void erase(int val) {
    int median = *l.rbegin();
    if (val > median) r.erase(r.find(val));
    else l.erase(l.find(val));
 
    if (r.size() > l.size()) {
        l.insert(*r.begin());
        r.erase(r.begin());
    } else if (l.size() > r.size() + 1) {
        r.insert(*l.rbegin());
        l.erase(prev(l.end()));
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, k) insert(a[i]);
    FOR(i, k, n) {
        cout << *l.rbegin() << ' ';
        erase(a[i - k]);
        insert(a[i]);
    }
    cout << *l.rbegin() << '\n';
    return 0;
}