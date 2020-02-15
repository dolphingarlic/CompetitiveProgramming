/*
COI 2014 GTA
- If we can get A to B and B to C, we can get A to C
    - So all molecules belong to some disjoint "classes"
- Basically there are only 24 "classes"
- Represent A, C, G, T as permutations such that when we compose
  them, the mutations happen
    - This lets us represent each class as a unique permutation since
      mutations preserve the permutations
- Complexity: O(N^2 * MAXLEN)
*/

#include <bits/stdc++.h>
using namespace std;

map<char, vector<int>> mp = {
    {'A', {1, 0, 3, 4, 5, 6, 7, 2}},
    {'C', {2, 5, 6, 0, 7, 3, 1, 4}},
    {'G', {7, 4, 5, 1, 6, 2, 0, 3}},
    {'T', {4, 7, 1, 6, 2, 0, 3, 5}}
};
            
vector<int> compose(vector<int> base, vector<int> trans) {
    vector<int> ret(8);
    for (int i = 0; i < 8; i++) ret[i] = trans[base[i]];
    return ret;
}

vector<int> perm[100];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        perm[i] = {0, 1, 2, 3, 4, 5, 6, 7};
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        for (char j : s) perm[i] = compose(perm[i], mp[j]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (perm[i] == perm[j]) cout << 1;
            else cout << 0;
        }
        cout << '\n';
    }
    return 0;
}
