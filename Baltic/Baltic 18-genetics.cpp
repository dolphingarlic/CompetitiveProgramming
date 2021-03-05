/*
Baltic 2018 Genetics
- We'll use hashing to solve this problem :D
- First, assign each clone a random number rnd[i]
- For each candidate, instead of checking it against all other clones individually,
  check it against all other clones simultaneously in O(M)
- Let D[j][c] = sum(rnd[i] : A[i][j] == c)
- Compute the "hash" of a candidate as sum(sum(D[j][c] : A[i][j] != c))
- If another clone x differs in exactly K places, it'll contribute K * rnd[x] to the hash
- This means that we'd expect the hash to be equal to K * (sum(rnd[x]) - rnd[i])
  if the current candidate is the answer; otherwise, they are not equal
- Using a 64-bit integer to store the hashes, we expect the probability of a collision
  to be 2^(-64)
- Complexity: O(NM)
*/

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

string s[4100];
ll rnd[4100], tot, sm[4100][4];

int idx(char c) {
    if (c == 'A') return 0;
    if (c == 'G') return 1;
    if (c == 'C') return 2;
    return 3;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        rnd[i] = rand();
        tot += rnd[i];
        cin >> s[i];
        for (int j = 0; j < m; j++) sm[j][idx(s[i][j])] += rnd[i];
    }

    for (int i = 0; i < n; i++) {
        ll hsh = 0;
        for (int j = 0; j < m; j++) hsh += tot - sm[j][idx(s[i][j])];
        if (hsh == k * (tot - rnd[i])) return cout << i + 1, 0;
    }
    return 0;
}
