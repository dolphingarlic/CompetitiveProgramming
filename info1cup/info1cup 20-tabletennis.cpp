/*
InfO(1) Cup 2020 Table Tennis
- If we know the best and worst players in Little Square's class, then we
  can identify all other players in the class
    - We use two pointers to do this; see code for more details
- We can therefore try out each prefix and suffix of impostors and check
  whether the "middle" part is good
- Using early breaks, this somehow runs in time? I don't know how but it does
- Complexity: O(K^2 N) ???
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, k;
ll a[150401];

void check(int pref, int suff) {
    vector<int> res;
    int lptr = pref + 1, rptr = suff - 1, bad = pref + n + k + 1 - suff;
    ll target = a[lptr] + a[rptr];
    while (lptr < rptr) {
        int sm = a[lptr] + a[rptr];
        if (sm == target) {
            res.push_back(lptr), res.push_back(rptr);
            lptr++, rptr--;

            if (res.size() == n) {
                sort(res.begin(), res.end());
                for (int i : res) cout << a[i] << ' ';
                exit(0);
            }
        } else if (sm < target)
            lptr++, bad++;
        else
            rptr--, bad++;
        
        if (bad > k) return;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i <= n + k; i++) cin >> a[i];
    for (int i = 0; i <= k; i++)
        for (int j = 0; j <= k - i; j++) check(i, n + k + 1 - j);
    return 0;
}
