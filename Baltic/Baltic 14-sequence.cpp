/*
Baltic 2014 Sequence
- Let each number K be represented as (X)Y, where X = K / 10 and Y = K % 10
    - Notice that now if we remove the last digit from each number, we have
      (X), (X), ..., (X+1), (X+1), ...
    - i.e. we have contiguous segments with the same prefix
    - We can thus merge them together and solve recursively
- For each number, consider the set of digits that it must contain
    - Initially, this set is simply the given digit for each number
    - If we know the last digit of some number, we can simply remove that digit from the set
    - When we only have 1 number, the answer is simply the smallest non-zero number
      with no leading zeroes we can make from the set
- Our solution is thus simply to brute force over each last digit and solve
  the subproblems recursively
    - There are N/10 subproblems because we group numbers in groups of 10
- Also, to efficiently represent the sets of digits, we use bitmasking since then
  we can just add masks for set unions
- Complexity: O(N log N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

ll ans = LLONG_MAX, pw[18];

void solve(vector<int> sections, ll curr = 0, int level = 0, bool had_zero = false) {
    if (curr > ans) return;
    int n = sections.size();

    if (n == 1) {
        int mask = sections[0];
        if (!mask) {
            if (!curr || had_zero) curr += pw[level];
        } else if (mask == 1) curr += pw[level + 1];
        else {
            if (mask & 1) {
                int mn = 10;
                for (int i = 9; i; i--) {
                    if (mask & (1 << i)) mn = i;
                }
                for (int i = 9; i; i--) {
                    if ((mask & (1 << i)) && i != mn) curr += i * pw[level++];
                }
                curr += mn * pw[++level];
            } else {
                for (int i = 9; i; i--) {
                    if (mask & (1 << i)) curr += i * pw[level++];
                }
            }
        }
        ans = min(ans, curr);
        return;
    }

    FOR(i, 0, 10) {
        vector<int> merged;
        int ins = 0;
        bool zero = false;

        int piv = i;
        FOR(j, 0, n) {
            zero |= (piv == 0 && (sections[j] & 1));
            ins |= (sections[j] & (~(1 << piv)));
            piv++;
            if (piv == 10) {
                merged.push_back(ins);
                ins = piv = 0;
            }
        }
        if (piv) merged.push_back(ins);

        solve(merged, curr + pw[level] * i, level + 1, zero);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> sections(n);
    FOR(i, 0, n) {
        int x;
        cin >> x;
        sections[i] = 1 << x;
    }
    pw[0] = 1;
    FOR(i, 1, 18) pw[i] = 10 * pw[i - 1];

    solve(sections);
    cout << ans;
    return 0;
}