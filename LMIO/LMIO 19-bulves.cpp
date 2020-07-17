/*
LMIO 2019 Bulves
- We want to transform the arrays A so that A[i] >= B[i] for each i
    - This means if we define the array C[i] = A[i] - B[i], then C must become a
      non-decreasing sequence with 0 <= C[i] <= C[N]
- Notice how each time we move a fertilizer to an adjacent position, exactly
  1 element of C changes and we increment the cost by 1
- This problem thus turns into https://codeforces.com/contest/713/problem/C and
  can be solved slope trick
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
using namespace std;

long long c[500001], ans = 0;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long a, b;
        cin >> a >> b;
        c[i] = c[i - 1] + a - b;
    }
    priority_queue<long long> pq;
    for (int i = 1; i <= n; i++) {
        if (c[i] > c[n]) {
            ans += c[i] - c[n];
            c[i] = c[n];
        } else if (c[i] < 0) {
            ans -= c[i];
            c[i] = 0;
        }
        pq.push(c[i]); pq.push(c[i]);
        ans += pq.top() - c[i];
        pq.pop();
    }
    cout << ans;
    return 0;
}
