#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define FOR(i, x, y) for(ll i = x; i < y; i++)
typedef long long ll;
using namespace std;
 
ll a[151];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, id = 1;
    cin >> n;
    
    vector<ll> v;
    FOR(i, 1, n + 1) {
        cout << id << ' ';
        for (auto& j : v) cout << j << ' ';
        cout << i << endl;
        ll x;
        cin >> x;
        if (x == id) {
            a[i] = id++;
            v.push_back(i);
        } else {
            ll l = 0, r = v.size() - 1;
            while (l != r) {
                ll mid = (l + r - 1) / 2;
                cout << mid - l + 2 << ' ' << i << ' ';
                FOR(j, l, mid + 1) cout << v[j] << ' ';
                cout << endl;
                ll k;
                cin >> k;
                if (k == mid - l + 1) r = mid;
                else l = mid + 1;
            }
            a[i] = a[v[l]];
        }
 
    }
 
    cout << "0 ";
    FOR(i, 1, n + 1) cout << a[i] << ' ';
    cout << endl;
    return 0;
}