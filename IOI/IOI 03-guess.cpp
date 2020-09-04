/*
IOI 2003 Guess Which Cow
- Similar to IOI 2015 Scales, for each set of candidate cows, DFS to
  find the optimal query to narrow the set down as much as possible
- This is fast enough because reasons
- Complexity: O(8NP * 2^(3P))
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

inline bool guess(int pos, int val) {
    cout << "Q " << pos + 1 << ' ' << char('X' + val) << '\n';
    bool ans;
    cin >> ans;
    return ans;
}

int n, p, prop[51][9];
map<ll, pair<int, pair<int, int>>> mem;

inline int popcount(ll mask) {
    int ans = 0;
    for (int i = 0; i < n; i++) if (mask & (1ll << i)) ans++;
    return ans;
}

int calc(ll mask) {
    if (mem.count(mask)) return mem[mask].first;
    if (popcount(mask) == 1) {
        mem[mask] = {0, {0, 0}};
        return 0;
    }

    int req = INT_MAX;
    pair<int, int> opt;
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < 3; j++) {
            ll pos = 0, neg = 0;
            for (int k = 0; k < n; k++) if (mask & (1ll << k)) {
                if (prop[k][i] == j) pos |= (1ll << k);
                else neg |= (1ll << k);
            }
            if (!pos || !neg) continue;
            int pot = max(calc(pos), calc(neg)) + 1;
            if (pot < req) {
                req = pot;
                opt = {i, j};
            }
        }
    }
    mem[mask] = {req, opt};
    return req;
}

int main() {
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            char c;
            cin >> c;
            prop[i][j] = c - 'X';
        }
    }
    ll curr = (1ll << n) - 1;
    calc(curr);
    while (popcount(curr) > 1) {
        int pos, val;
        tie(pos, val) = mem[curr].second;
        bool res = guess(pos, val);
        for (int i = 0; i < n; i++) if (curr & (1ll << i)) {
            if (res ^ (prop[i][pos] == val)) curr -= (1ll << i);
        }
    }
    int ans;
    for (int i = 0; i < n; i++) if (curr & (1ll << i)) ans = i;
    cout << "C " << ans + 1 << '\n';
}

/*
50 4
X X X X
X X X Y
X X X Z
X X Y X
X X Y Y
X X Y Z
X X Z X
X X Z Y
X X Z Z
X Y X X
X Y X Y
X Y X Z
X Y Y X
X Y Y Y
X Y Y Z
X Y Z X
X Y Z Y
X Y Z Z
X Z X X
X Z X Y
X Z X Z
X Z Y X
X Z Y Y
X Z Y Z
X Z Z X
X Z Z Y
X Z Z Z
Y X X X
Y X X Y
Y X X Z
Y X Y X
Y X Y Y
Y X Y Z
Y X Z X
Y X Z Y
Y X Z Z
Y Y X X
Y Y X Y
Y Y X Z
Y Y Y X
Y Y Y Y
Y Y Y Z
Y Y Z X
Y Y Z Y
Y Y Z Z
Y Z X X
Y Z X Y
Y Z X Z
Y Z Y X
Y Z Y Y
*/