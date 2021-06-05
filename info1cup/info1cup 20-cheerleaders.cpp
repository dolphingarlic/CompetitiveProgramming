/*
InfO(1) Cup 2020 Cheerleaders
- Consider the position P[i] of cheerleader i
    - Big swap: P[i] := P[i] ^ (1 << N - 1)
    - Big split: P[i] := (P[i] >> 1) + ((P[i] & 1) << N - 1)
        - Basically a cyclic bit shift right
- This means that we can essentially XOR the positions of all cheerleaders
  by some constant M and do a cyclic bit shift of C <= N positions
- For a fixed C, we can find the optimal M greedily
    - For each bit of M, we find the number of inversions resulting from
      it being 0 or 1
    - Then we set M to the smaller of the two potential values
    - To speed this up, we use merge sort and sort in-place
- Complexity: O(N^2 * 2^N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int n, h[1 << 17], at[1 << 17], cp[1 << 17];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    for (int i = 0; i < (1 << n); i++) {
        cin >> h[i];
        at[h[i]] = i;
    }

    ll mn = LLONG_MAX;
    string best_seq;
    for (int shift = 0; shift < max(1, n); shift++) {
        int mask = 0;
        ll inv_tot = 0;
        for (int i = 0; i < (1 << n); i++) cp[i] = h[i];
        for (int i = 0; i < n; i++) {
            ll inv_0 = 0, inv_1 = 0;

            for (int j = 0; j < (1 << n); j += 1 << i + 1) {
                int lptr = j, rptr = j + (1 << i), l_used = 0, r_used = 0;
                vector<int> sorted;
                while (lptr < j + (1 << i) && rptr < j + (1 << i + 1)) {
                    if (cp[lptr] > cp[rptr]) {
                        inv_1 += l_used;
                        sorted.push_back(cp[rptr]);
                        rptr++, r_used++;
                    } else {
                        inv_0 += r_used;
                        sorted.push_back(cp[lptr]);
                        lptr++, l_used++;
                    }
                }
                while (lptr < j + (1 << i)) {
                    inv_0 += r_used;
                    sorted.push_back(cp[lptr]);
                    lptr++, l_used++;
                }
                while (rptr < j + (1 << i + 1)) {
                    inv_1 += l_used;
                    sorted.push_back(cp[rptr]);
                    rptr++, r_used++;
                }
                for (int k = 0; k < (1 << i + 1); k++) cp[j + k] = sorted[k];
            }

            if (inv_0 > inv_1) mask += 1 << i;
            inv_tot += min(inv_0, inv_1);
        }

        if (inv_tot < mn) {
            string seq;
            for (int i = 0; i < shift; i++) seq += "2";
            for (int i = 0; i < n; i++) {
                seq += "2";
                if (mask & (1 << i)) seq += "1";
            }
            mn = inv_tot;
            best_seq = seq;
        }

        for (int i = 0; i < (1 << n); i++) {
            at[i] = (at[i] >> 1) + ((at[i] & 1) << n - 1);
            h[at[i]] = i;
        }
    }
    cout << mn << '\n' << best_seq;
    return 0;
}
