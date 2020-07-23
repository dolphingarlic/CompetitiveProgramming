/*
Baltic 2020 Colors
- Binary search + randomisation to avoid collisions
- Complexity: log(N) + 1 queries
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

map<ll, bool> used;

bool ask(ll i) {
    used[i] = 1;
    cout << "? " << i << endl;
    bool x;
    cin >> x;
    return x;
}

void solve(ll n) {
    used.clear();
    ll l = 1, r = n;
    vector<ll> im;
    ll l1 = l, r1 = r;
    while (l1 < r1) {
        ll mid = (l1 + r1) / 2;
        im.push_back(mid);
        l1 = mid + 1;
    }
    reverse(im.begin(), im.end());
    ll curr = 1;
    FOR(i, 0, im.size()) {
        if (i & 1) curr -= im[i];
        else curr += im[i];
    }
    ask(curr);
    while (l != r) {
        ll mid = (l + r) / 2;
        if (curr + mid <= n && !used[curr + mid]) {
            curr += mid;
            if (!ask(curr)) l = mid + 1;
            else r = mid;
        } else if (curr - mid >= 1 && !used[curr - mid]) {
            curr -= mid;
            if (!ask(curr)) l = mid + 1;
            else r = mid;
        } else {
            l1 = l, r1 = r;
            im.clear();
            while (l1 < r1) {
                ll mid = (l1 + r1) / 2;
                im.push_back(mid);
                l1 = mid + 1;
            }
            reverse(im.begin(), im.end());
            curr = 1;
            FOR(i, 0, im.size()) {
                if (i & 1) curr -= im[i];
                else curr += im[i];
            }
            if (curr >= r + 1 - curr) curr = r + 1 - curr;
            curr = rand() % curr + 1;
            while (used[curr] || used[curr + mid] || used[curr - mid]) ++curr;
            ask(curr);
        }
    }
    cout << "= " << l << endl;
}

int main() {
    srand(69420);
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        solve(n);
    }
    return 0;
}