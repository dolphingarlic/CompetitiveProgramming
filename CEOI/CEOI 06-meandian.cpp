/*
CEOI 2006 Meandian
- If N = 5, then we can find the median index and value using 5 queries
- For N > 5, find the median index and value of any 5 values, erase that index, and repeat
- Complexity: 5N - 20 queries
*/

#include "libmean.h"
#include <bits/stdc++.h>
using namespace std;

int ans[100], c[5];

int main() {
    int n = Init();
    fill(ans, ans + n, -1);
    queue<int> cand;
    for (int i = 1; i <= n; i++) cand.push(i);
    while (cand.size() > 4) {
        for (int i = 0; i < 5; i++) {
            c[i] = cand.front();
            cand.pop();
        }
        vector<pair<int, int>> occ = {
            {Meandian(c[0], c[1], c[2], c[3]), c[4]},
            {Meandian(c[0], c[1], c[2], c[4]), c[3]},
            {Meandian(c[0], c[1], c[3], c[4]), c[2]},
            {Meandian(c[0], c[2], c[3], c[4]), c[1]},
            {Meandian(c[1], c[2], c[3], c[4]), c[0]}
        };
        sort(occ.begin(), occ.end());
        ans[occ[2].second - 1] = occ[0].first + occ[4].first - occ[2].first;
        for (int i = 0; i < 5; i++) if (i != 2) cand.push(occ[i].second);
    }
    Solution(ans);
}
