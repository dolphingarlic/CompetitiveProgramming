/*
COI 2016 Palinilap
- Firstly, we need to find the weight of the sample word
    - Notice how the weight is simply the sum of the radii
      of the longest palindromes centered on each letter
    - To find these radii, we can either use Manacher's algorithm (which I don't know)
      or we can binary search for each radius
        - To binary search, use a polynomial hash (N.B. BASE 64 HASHING FAILS ON SUBTASK 3 TEST 18)
- Next, we need to find how the weight changes when we change a letter
- We have 2 cases: palindromes are created or palindromes are destroyed
    - If we change the letter at position i to j, a palindrome is created iff
        - i is on the "boundary" of some palindrome
        - j is equal to the letter on the other "boundary" of the same palindrome
    - If we change the letter at position i to any letter, the number of palindromes destroyed
      can be similarly determined
- We can use a sweep line to calculate these changes and choose the best one
- Complexity: O(N (log N + ALPHABET_SIZE))
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const ll M = 1e9 + 9, P = 9973;

ll pw[100001];

int n;
string s[2];
ll hsh[100001][2], created[100001][26], destroyed[100001][2];

void calc_hashes() {
    hsh[0][0] = hsh[0][1] = 1;
    FOR(i, 0, n) FOR(j, 0, 2)
        hsh[i + 1][j] = ((hsh[i][j] * P) % M + s[j][i]) % M;
}

ll get_hash(int a, int b, bool reverse) {
    return (hsh[b + 1][reverse] - (hsh[a][reverse] * pw[b - a + 1]) % M + M) % M;
}

bool is_palindrome(int a, int b, int c, int d) {
    return get_hash(a, b, false) == get_hash(n - d - 1, n - c - 1, true);
}

int main() {
    cin >> s[0];
    n = s[0].size();
    s[1] = s[0];
    reverse(s[1].begin(), s[1].end());
    
    pw[0] = 1;
    FOR(i, 0, n) pw[i + 1] = (P * pw[i]) % M;
    calc_hashes();
    
    ll base = 0;
    FOR(i, 0, n) FOR(j, i, i + 2) {
        int l = 0, r = min(i + 1, n - j);
        while (l != r) {
            int mid = (l + r + 1) / 2;
            if (is_palindrome(i - mid + 1, i, j, j + mid - 1)) l = mid;
            else r = mid - 1;
        }
        int rad = r;
        base += rad;
        
        if (i == j) {
            destroyed[j + 1][0]--, destroyed[j + rad][0]++;
            destroyed[j + 1][1] += j + rad, destroyed[j + rad][1] -= j + rad;

            destroyed[i - rad + 1][0]++, destroyed[i][0]--;
            destroyed[i - rad + 1][1] -= i - rad, destroyed[i][1] += i - rad;
        } else {
            destroyed[j][0]--, destroyed[j + rad][0]++;
            destroyed[j][1] += j + rad, destroyed[j + rad][1] -= j + rad;

            destroyed[i - rad + 1][0]++, destroyed[i + 1][0]--;
            destroyed[i - rad + 1][1] -= i - rad, destroyed[i + 1][1] += i - rad;
        }
        
        int x = i - rad, y = j + rad;
        if (x < 0 || y >= n) continue;
        
        rad++;
        l = 0, r = min(i + 1, n - j) - rad;
        while (l != r) {
            int mid = (l + r + 1) / 2;
            if (is_palindrome(x - mid, x - 1, y + 1, y + mid)) l = mid;
            else r = mid - 1;
        }

        created[x][s[0][y] - 'a'] += r + 1;
        created[y][s[0][x] - 'a'] += r + 1;
    }
    
    ll best = 0, x = 0, y = 0;
    FOR(i, 0, n) {
        x += destroyed[i][0], y += destroyed[i][1];
        FOR(j, 0, 26) if (i != s[0][j] - 'a') {
            best = max(best, created[i][j] - i * x - y);
        }
    }
    
    cout << base + best;
    return 0;
}