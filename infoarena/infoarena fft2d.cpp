/*
Infoarena FFT2D
- Firstly, notice that there is at most 1 path between 2 nodes
    - This is because each node has only 2 edges to 2 disjoint "subtrees"
    - So we can simply find the number of paths that each black node blocks
      and subtract that from our answer, which is initially 4^(F - 1)
- To find the number of paths, we use dp
    - The next observation is that there is a path from (h1, a) to (h2, b) iff
      h1 < h2 and the only bits that differ between a and b are in positions in
      the range [h1, h2]
    - This means we can find the sum of dp of black "children" of each black
      node in O(F log T) using a map
- Complexity: O(FFT log T)
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
// Creates a mask 11...00...11...
int mask(int f, int pref, int suff) {
    return ((1 << f) - 1) ^ ((1 << (f - pref)) - 1) ^ ((1 << (f - suff)) - 1);
}
 
vector<int> nodes[31];
map<ll, ll> dp[31][31];
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);
    int f, t;
    cin >> f >> t;
    f--;
    for (int i = 0; i < t; i++) {
        int h, x;
        cin >> h >> x;
        nodes[h].push_back(x);
    }
    
    ll ans = 1ll << (2 * f);
    for (int i = f; ~i; i--) {
        for (int x : nodes[i]) {
            // Number of paths down
            ll subtr = 1ll << (f - i);
            for (int j = i + 1; j <= f; j++)
                subtr -= dp[i][j][mask(f, i, j) & x];
            
            ans -= subtr * (1ll << i);
            for (int j = i - 1; ~j; j--)
                dp[j][i][mask(f, j, i) & x] += subtr;
        }
    }
    cout << ans;
    return 0;
}
