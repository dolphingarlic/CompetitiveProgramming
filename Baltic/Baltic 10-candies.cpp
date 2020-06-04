/*
Baltic 2010 Candies
- Firstly, we run knapsack N times to see how many distinct sums we
  can make if we exclude each candy
- The candy we change will be the minimum one with the largest count
- Notice how we want to double the number of distinct values we can make
    - Just change the one candy to sum(others) + 1
- Next, notice that if we have 2 disjoint subsets A and B, we can't
  change the candy to sum(A) - sum(B) or else we don't double the count
- This means we can just run another knapsack but also allowing -a[i]
- The answer is the first positive number we can't make with this new
  knapsack
- We use bitset to speed things up
- Complexity: O(BN^3 / 64)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

int a[100];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    sort(a, a + n, greater<int>());

    pair<int, int> best = {0, -1};
    FOR(i, 0, n) {
        bitset<700000> dp;
        dp[0] = 1;
        FOR(j, 0, n) {
            if (j == i) continue;
            dp |= dp << a[j];
        }
        best = max(best, {dp.count(), i});
    }
    
    bitset<1400000> dp;
    dp[700000] = 1;
    FOR(i, 0, n) {
        if (i == best.second) continue;
        dp |= (dp << a[i]) | (dp >> a[i]);
    }

    cout << a[best.second] << ' ';
    FOR(i, 1, 700000)
        if (!dp[700000 + i])
            return cout << i, 0;
    return 0;
}