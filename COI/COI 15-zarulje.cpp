/*
COI 2015 Zarulje
- Firstly, notice that if we turn off a light bulb (WLOG to the left) with power P, then
  we keep turning off lightbulbs to the left as long as their power is >P
- This means for some position, we only need to consider the "important" light bulbs
    - E.g. If we're on X, we could have L = [A, B, C] and R = [D, E, F] where A <= B <= C and D >= E >= F
        - X has no impact on these 2 lists other than its position
    - To find these light bulbs, we sweep from left to right/right to left and use a monotone stack
    - After we have these important light bulbs, let l_cnt and r_cnt be the number of times each
      light bulb with some power appears in the left or right list
    - Notice how the answer is simply prod((l_cnt[i] + r_cnt[i]) choose l_cnt[i])
    - This gives us a O(KN log N) algorithm
- To speed it up, notice how each bulb is inserted and popped at most once from the stack
    - So for each position, keep lists of which values are inserted or popped at that point in the sweep
    - ans[1] = ans[N] = 1 always
    - In a single sweep, we can then update the answer efficiently (by dividing by the old binomial thing and
      multiplying by the new)
- Complexity: O(N log N + K)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

const ll mult(const ll &A, const ll &B) { return (A * B) % MOD; }

int a[200002], l_cnt[200002], r_cnt[200002];
ll fact[200002]{1}, inv_fact[200002]{1}, ans[200002]{1};
vector<int> l_ers[200002], r_ers[200002];

const ll choose(const ll &A, const ll &B) { return mult(mult(fact[A], inv_fact[B]), inv_fact[A - B]); }

const ll inv_choose(const ll &A, const ll &B) { return mult(mult(inv_fact[A], fact[B]), fact[A - B]); }

ll expo(ll A, ll B) {
    ll ans = 1;
    while (B) {
        if (B & 1) ans = mult(ans, A);
        A = mult(A, A);
        B >>= 1;
    }
    return ans;
}

void update(int pos, int val, bool l, bool add) {
    ans[pos] = mult(ans[pos], inv_choose(l_cnt[val] + r_cnt[val], l_cnt[val]));
    if (l) {
        if (add) l_cnt[val]++;
        else l_cnt[val]--;
    } else {
        if (add) r_cnt[val]++;
        else r_cnt[val]--;
    }
    ans[pos] = mult(ans[pos], choose(l_cnt[val] + r_cnt[val], l_cnt[val]));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, k;
    cin >> n >> k;
    FOR(i, 1, n + 1) {
        cin >> a[i];
        fact[i] = mult(fact[i - 1], i);
        inv_fact[i] = expo(fact[i], MOD - 2);
    }
    
    stack<int> stck;
    FOR(i, 1, n + 1) {
        while (stck.size() && stck.top() > a[i]) {
            l_ers[i].push_back(stck.top());
            stck.pop();
        }
        stck.push(a[i]);
    }
    while (stck.size()) stck.pop();
    for (int i = n; i; i--) {
        while (stck.size() && stck.top() > a[i]) {
            r_ers[i].push_back(stck.top());
            r_cnt[stck.top()]--;
            stck.pop();
        }
        stck.push(a[i]);
        r_cnt[a[i]]++;
    }

    FOR(i, 1, n + 1) {
        ans[i] = ans[i - 1];
        if (i > 1) {
            update(i, a[i - 1], 1, 1);
            for (int j : l_ers[i - 1]) update(i, j, 1, 0);
        }
        update(i, a[i], 0, 0);
        for (int j : r_ers[i]) update(i, j, 0, 1);
    }

    while (k--) {
        int pos;
        cin >> pos;
        cout << ans[pos] << '\n';
    }
    return 0;
}