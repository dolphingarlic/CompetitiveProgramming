/*
IOI 2016 Shortcut
- The diameter will always go from a secondary station to another,
  if we assume that d[i] == 0 means a secondary station still exists
- Let p[i] = sum(l[i] for i from 0 to i - 1)
- Binary search for the answer. Let our current candidate be M
- Firstly, we only care about a pair of stations i < j if:
    d[j] + d[i] + p[j] - p[i] > M
  because we can just go from i to j without the shortcut
- M is good if there exist x < y (both elements of p) such that
  for each pair of stations i < j that we care about:
    C + d[j] + d[i] + |p[j] - y| + |p[i] - x| <= M
- We can rearrange this inequality to get
    |p[j] - y| + |p[i] - x| <= M - C - d[j] - d[i]
  which defines a square rotated by 45 degrees centered at (p[i], p[j])
- The problem now becomes checking whether the intersection of all
  such squares contains a point (x, y) where x < y and x and y are in p
- We can expand the above inequality to get a bunch of inequalities
  defining half-planes e.g.
    x + y >= C - M + d[j] + p[j] + d[i] + p[i]
- Since we want to find the half plane intersection, we basically want to
  find the maximum values of the right-hand sides of those inequalities
- We can sort the stations by d[i] + p[i] and d[i] - p[i] in two lists,
  and then use two pointers to maintain a prefix/suffix maximum
    - See the code for more details
- However, we might include (secondary i) -> (main i) -> (secondary i)
  in the answer if we're not careful (which isn't allowed)
    - To fix this, store the two maximum values of d[i] + p[i] / d[i] - p[i]
- To check whether a good point exists in the half-plane intersection,
  maintain two pointers pointing to the closest points above and below
  the intersection
    - Since these pointers are bitonic, this works in amortized O(N) time
- Complexity: O(N log ANS)
*/

#include "shortcut.h"

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll INF = 1e16;

ll p[1000000], half_plane[4];
pair<ll, int> ord1[1000000], ord2[1000000];

ll find_shortcut(int n, vector<int> l, vector<int> d, int c) {
    for (int i = 1; i < n; i++) p[i] = p[i - 1] + l[i - 1];

    // Order by d[i] + p[i] and d[i] - p[i]
    for (int i = 0; i < n; i++)
        ord1[i] = {d[i] + p[i], i}, ord2[i] = {d[i] - p[i], i};
    sort(ord1, ord1 + n);
    sort(ord2, ord2 + n);

    // Binary search for the answer
    ll ans = 0;
    for (ll i = 1ll << 48; i; i >>= 1) {
        ll mid = ans + i;

        // Reset maximums and minimums
        for (int j = 0; j < 4; j++) half_plane[j] = -INF;
        ll mx1 = -INF, mx2 = -INF, smx1 = -INF, smx2 = -INF;

        for (int i = 0, j = n - 1; i < n; i++) {
            while (~j && ord1[i].first + ord2[j].first > mid) {
                ll tmp1 = d[ord2[j].second] + p[ord2[j].second];
                if (tmp1 > mx1) smx1 = mx1, mx1 = tmp1;
                else if (tmp1 > smx1) smx1 = tmp1;

                ll tmp2 = d[ord2[j].second] - p[ord2[j].second];
                if (tmp2 > mx2) smx2 = mx2, mx2 = tmp2;
                else if (tmp2 > smx2) smx2 = tmp2;

                j--;
            }
            // Update the half planes
            ll use1 = (d[ord1[i].second] + p[ord1[i].second] == mx1 ? smx1 : mx1);
            ll use2 = (d[ord1[i].second] - p[ord1[i].second] == mx2 ? smx2 : mx2);
            half_plane[0] = max(half_plane[0], c - mid + d[ord1[i].second] + p[ord1[i].second] + use1);
            half_plane[1] = max(half_plane[1], c - mid + d[ord1[i].second] - p[ord1[i].second] + use1);
            half_plane[2] = max(half_plane[2], c - mid + d[ord1[i].second] + p[ord1[i].second] + use2);
            half_plane[3] = max(half_plane[3], c - mid + d[ord1[i].second] - p[ord1[i].second] + use2);
        }

        // Check that the half-plane intersection contains a good point
        bool bad = true;
        // Point (x, y) is below the half-plane intersection if y < max(-x + half_plane[0], x + half_plane[1])
        // Point (x, y) is above the half-plane intersection if y > min(-x - half_plane[3], x - half_plane[2])
        for (int i = 0, lower = n - 1, upper = 0; i < n; i++) {
            while (~lower && p[lower] >= max(-p[i] + half_plane[0], p[i] + half_plane[1]))
                lower--;
            while (lower + 1 < n && p[lower + 1] < max(-p[i] + half_plane[0], p[i] + half_plane[1]))
                lower++;
            while (upper < n && p[upper] <= min(-p[i] - half_plane[3], p[i] - half_plane[2]))
                upper++;
            while (upper && p[upper - 1] > min(-p[i] - half_plane[3], p[i] - half_plane[2]))
                upper--;
            if (upper - lower > 1) {
                bad = false;
                break;
            }
        }
        if (bad) ans = mid;
    }
    return ans + 1;
}
