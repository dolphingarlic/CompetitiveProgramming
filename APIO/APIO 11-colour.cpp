/*
APIO 2011 Table Colouring
- Let colour(x, y) = 1 if block (x, y) is blue and 0 otherwise
- Firstly, notice that if we already know the colour of 3 cells in a 2x2 table,
  the last cell's colour is already determined
- From this, we get that colour(x, y) = ~(colour(x - 1, y - 1) ^ colour(x - 1, y) ^ colour(x, y - 1))
  for all x, y > 1
- For convenience, add a row 0 and column 0
- After analysing an arbitrary table in a spreadsheet, we find that we actually have
  colour(x, y) = ~(colour(0, 0) ^ colour(0, y) ^ colour(x, 0) ^ ((x & 1) && (y & 1))
  for all x, y > 1
- WLOG, let (0, 0) be a red cell (since it being a blue cell doesn't change the number of colourings)
- For all x, colour(x, 1) is an independent variable. Similarly, colour(1, y) is independent

- For each already-coloured cell (x, y), add a bidirectional edge between (x, 0) and (0, y)
- This creates some connected components. Let the number be K
- The answer is thus either 2^(K - 1) or 0
    - This is because each node in a connected component is dependent on the other nodes
    - Also the answer can be 0 if it simply isn't possible to colour the table
- To check if it is possible to colour the table, we just use 2-SAT
    - We can actually do this with DSU (http://momo-funnycodes.blogspot.com/2012/10/codeforces-228e-road-to-berland-is.html)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int MOD = 1e9;

int x[100001], y[100001], cmp[400001];

int find(int A) {
    while (A != cmp[A]) cmp[A] = cmp[cmp[A]], A = cmp[A];
    return A;
}
void onion(int A, int B) { cmp[find(A)] = cmp[find(B)]; }

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    FOR(i, 0, 2 * (n + m)) cmp[i] = i;

    FOR(i, 0, k) {
        int c;
        cin >> x[i] >> y[i] >> c;
        c ^= (x[i] & 1) && (y[i] & 1);

        if (c) {
            onion(x[i], y[i] + n);
            onion(x[i] + m + n, y[i] + 2 * n + m);
        } else {
            onion(x[i] + m + n, y[i] + n);
            onion(x[i], y[i] + 2 * n + m);
        }
    }

    int cnt = -1;
    FOR(i, 0, n + m) {
        if (find(i) == find(i + n + m)) return cout << "0", 0;
        if (find(i) == i) cnt++;
    }

    int ans = 1;
    FOR(i, 0, cnt) ans = (ans * 2) % MOD;
    cout << ans;
    return 0;
}