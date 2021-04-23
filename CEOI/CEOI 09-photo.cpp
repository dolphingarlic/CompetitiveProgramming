/*
CEOI 2009 Photo
- First, let's assume that all x coordinates are distinct
    - We can enforce this by only caring about the points with
      maximum y coordinate for each x coordinate
- Furthermore, sort the points by x coordinate
- If we have two photos, then it's optimal for them either to be:
    - Nested (i.e. l1 < l2 < r2 < r1)
    - Disjoint (i.e. l1 < r1 < l2 < r2)
    - If not, then we can shrink one of the photos so that they
      satisfy this property and still get the same result
- This suggests that we can use range DP to solve this:
    dp[i][j] = Minimum no. of photos needed to cover points i to j
- There are two cases:
    - We split the range into two disjoint ranges (see case 1)
    - We use a wide photo to cover the points with small y coordinate
      in the entire range (see case 2)
- Complexity: O(N^3)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int dp[101][101];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, a;
    cin >> n >> a;
    map<int, int> has_x;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        if (has_x.count(x)) has_x[x] = max(has_x[x], y);
        else has_x[x] = y;
    }
    vector<pair<int, int>> p = {{0, 0}};
    for (pair<int, int> i : has_x) p.push_back(i);
    n = p.size() - 1;

    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n - k + 1; i++) {
            int j = i + k - 1;
            // We can always cover the points in k photos
            dp[i][j] = k;
            if (i == j) continue;
            // Case 1: We split the range into two smaller ranges
            for (int l = i; l < j; l++)
                dp[i][j] = min(dp[i][j], dp[i][l] + dp[l + 1][j]);
            // Case 2: We use a wide photo to cover the entire range
            int height = a / (p[j].first - p[i].first);
            if (height < p[i].second || height < p[j].second) continue;
            int sm = 1;
            for (int l = i + 1, r = i + 1; r <= j; r++) {
                if (p[r].second <= height) {
                    sm += dp[l][r - 1];
                    l = r + 1;
                }
            }
            dp[i][j] = min(dp[i][j], sm);
        }
    }
    cout << dp[1][n];
    return 0;
}
