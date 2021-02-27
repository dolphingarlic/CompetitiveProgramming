/*
Baltic 2017 Plusminus
- The grid is determined by the first row and column, so let's focus on those first
- In a valid grid, either the first row or column must go 1/-1/1/-1/... (or vice versa),
  while the other can do whatever it wants
    - WLOG assume that it's the first column that does this; we can just flip everything
      and calculate the answer again to account for the other case
    - Also, we must check whether the grid is still valid if both the first row and column
      do this, and if it is, subtract 1 from the answer
- val[x, y] = val[x, 1] * val[1, y] * val[1, 1]
- Therefore, we can collect Matt's measurements by column and check that they're consistent
    - If they are, then there 2^(M - number of used columns) ways to construct the grid
    - Otherwise, there are 0
- We can use fast exponentiation to calculate this quickly
- See APIO 2011 Coloring for a very similar problem
- Complexity: O(K log N)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MOD = 1e9 + 7;

ll expo(ll base, int pow) {
    ll ans = 1;
    while (pow) {
        if (pow & 1) ans = (ans * base) % MOD;
        pow >>= 1;
        base = (base * base) % MOD;
    }
    return ans;
}

ll count_ways(int n, int m, map<int, vector<pair<int, char>>> mp) {
    for (auto& i : mp) {
        bool sgn = (i.second[0].first & 1) ^ (i.second[0].second == '+');
        for (pair<int, char> j : i.second) {
            bool needed = (j.first & 1) ^ (j.second == '+');
            if (sgn ^ needed) return 0;
        }
    }
    return expo(2, n - mp.size());
}

int check_both(int n, int m, map<int, vector<pair<int, char>>> mp) {
    if (mp.size() == 0) return 2;
    bool sgn = (mp.begin()->first & 1) ^ (mp.begin()->second[0].first & 1) ^ (mp.begin()->second[0].second == '+');
    for (auto& i : mp) {
        for (pair<int, char> j : i.second) {
            bool needed = (i.first & 1) ^ (j.first & 1) ^ (j.second == '+');
            if (sgn ^ needed) return 0;
        }
    }
    return 1;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    map<int, vector<pair<int, char>>> horiz, vert;
    while (k--) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        horiz[x].push_back({y, c});
        vert[y].push_back({x, c});
    }
    cout << (count_ways(n, m, horiz) + count_ways(m, n, vert) - check_both(n, m, horiz)) % MOD;
    return 0;
}
