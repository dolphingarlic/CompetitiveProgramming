/*
CEOI 2013 Board
- Assume WLOG that A is to the left of B
- Firstly, notice that the optimal path goes up from A, then right, then down to B
- If we number the nodes of the board like nodes of a segtree, then
    - '1': Multiply position by 2
    - '2': Multiply position by 2 and add 1
    - 'U': Divide position by 2
    - 'L': Decrement position
    - 'R': Increment position
- We can use a modified bigint to store the positions
- Try out each level we can move up to, starting from 0
- Complexity: O(N)
*/

#include <bits/stdc++.h>
#define FOR(i, x, y) for (int i = x; i < y; i++)
typedef long long ll;
using namespace std;

const int BASE = 62;

int len_a, len_b;
ll big_a[100000], big_b[100000];

void read(ll *big, int &len) {
    big[0] = 1ll << (BASE - 1);
    len = 1;

    string s;
    cin >> s;
    for (char i : s) {
        switch (i) {
            case '1':
                big[len / BASE] &= ~(1ll << (BASE - 1 - len % BASE));
                len++;
                break;
            case '2':
                big[len / BASE] |= 1ll << (BASE - 1 - len % BASE);
                len++;
                break;
            case 'L':
                big[(len - 1) / BASE] -= 1ll << (BASE - 1 - (len - 1) % BASE);
                for (int j = (len - 1) / BASE; big[j] < 0; j--) {
                    big[j] += 1ll << BASE;
                    big[j - 1]--;
                }
                break;
            case 'R':
                big[(len - 1) / BASE] += 1ll << (BASE - 1 - (len - 1) % BASE);
                for (int j = (len - 1) / BASE; big[j] >= 1ll << BASE; j--) {
                    big[j] -= 1ll << BASE;
                    big[j - 1]++;
                }
                break;
            default:
                len--;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    read(big_a, len_a);
    read(big_b, len_b);

    int ans = INT_MAX, a1 = 0;
    FOR(i, 0, min(len_a, len_b)) {
        a1 = 2 * a1 + (big_a[i / BASE] >> (BASE - 1 - i % BASE) & 1) - (big_b[i / BASE] >> (BASE - 1 - i % BASE) & 1);
        if (abs(a1) > ans) break;
        ans = min(ans, abs(a1) + len_a + len_b - 2 * i - 2);
    }
    cout << ans;
    return 0;
}