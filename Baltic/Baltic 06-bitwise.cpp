/*
Baltic 2006 Bitwise Expressions
- Since we want to maximize this, we probably want to check for each bit from
  left (greatest) to right (least) if it's possible for each subexpression to have it
    - This can easily be done by checking whether 2^pos is in range
      for each subexpression
- The next problem is finding which variable to assign this bit to in each
  subexpression to maximize the thing
    - It turns out that we can just assign the bit to any variable with it in
      range, but only one variable
    - Notice how if we assign 1 to a bit for a variable, the lowerbound becomes 0
      and if we assign 0 to a bit, the upperbound (only considering the rest of the bits)
      becomes 2^pos - 1
        - So when we assign values, we should update lo and hi accordingly
        - This only happens if hi[i] & (1 << pos) != lo[i] & (1 << pos) though
- Honestly I have no idea why the greedy works, but it does
- Complexity: O(N log^2 MAXV)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int n, p, sz[101], lo[101], hi[101];

bool check(int pos) {
    for (int i = 0, idx = 0; idx < p; i += sz[idx], idx++) {
        bool possible = false;
        FOR(j, i, i + sz[idx]) if (hi[j] & (1 << pos)) possible = true;
        if (!possible) {
            FOR(j, 0, n) {
                if ((hi[j] & (1 << pos)) && !(lo[j] & (1 << pos))) {
                    FOR(k, 0, pos) hi[j] |= (1 << k);
                }
            }
            return false;
        }
    }

    for (int i = 0, idx = 0; idx < p; i += sz[idx], idx++) {
        bool assigned = false;
        FOR(j, i, i + sz[idx]) if ((hi[j] & (1 << pos)) && (lo[j] & (1 << pos))) assigned = true;
        FOR(j, i, i + sz[idx]) {
            if ((hi[j] & (1 << pos)) && !(lo[j] & (1 << pos))) {
                if (!assigned) {
                    assigned = true;
                    lo[j] = 0;
                } else FOR(k, 0, pos) hi[j] |= (1 << k);
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> p;
    FOR(i, 0, p) cin >> sz[i];
    FOR(i, 0, n) cin >> lo[i] >> hi[i];

    int ans = 0;
    for (int i = 31; ~i; i--) if (check(i)) ans |= 1 << i;
    cout << ans;
    return 0;
}