#include <bits/stdc++.h>
#pragma GCC Optimize("O3")
#define FOR(i, x, y) for (int i = x; i < y; i++)
#define MOD 1000000007
typedef long long ll;
using namespace std;

int n;
int a[100000], b[100000];
bool sa[100000], sb[100000];
bool sign_a[100000], sign_b[100000];
pair<bool, int> moves_a[100000], moves_b[100000];

int main() {
    iostream::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, 0, n) cin >> a[i];
    FOR(i, 0, n) cin >> b[i];
    FOR(i, 0, n) {
        int x;
        cin >> x;
        if (x == 1) sa[i] = true, sb[i] = true;
        else if (x == 2) sa[i] = false, sb[i] = true;
        else if (x == 3) sa[i] = false, sb[i] = false;
        else sa[i] = true, sb[i] = false;
    }

    sort(a, a + n);
    sort(b, b + n);

    // Handle a
    int same = n - 1, indx = 0;
    FOR(i, 0, n - 1) {
        if (sa[i] ^ sa[i + 1]) same--;
    }
    if ((same & 1) == sa[0]) FOR(i, 0, n) sign_a[i] = (i & 1);
    else FOR(i, 0, n) sign_a[i] = !(i & 1);
    int lptr = same - 1, rptr = same + 1;
    moves_a[indx++] = {sign_a[same], a[same]};
    FOR(i, 0, n - 1) if (sa[i] ^ sa[i + 1]) {
        moves_a[indx++] = {sign_a[rptr], a[rptr++]};
    } else moves_a[indx++] = {sign_a[lptr], a[lptr--]};

    // Handle b
    same = n - 1, indx = 0;
    FOR(i, 0, n - 1) {
        if (sb[i] ^ sb[i + 1]) same--;
    }
    if ((same & 1) == sb[0]) FOR(i, 0, n) sign_b[i] = (i & 1);
    else FOR(i, 0, n) sign_b[i] = !(i & 1);
    lptr = same - 1, rptr = same + 1;
    moves_b[indx++] = {sign_b[same], b[same]};
    FOR(i, 0, n - 1) if (sb[i] ^ sb[i + 1]) {
        moves_b[indx++] = {sign_b[rptr], b[rptr++]};
    } else moves_b[indx++] = {sign_b[lptr], b[lptr--]};

    FOR(i, 0, n) cout << (moves_a[i].first ? '+' : '-') << moves_a[i].second << ' '
                      << (moves_b[i].first ? '+' : '-') << moves_b[i].second << '\n';
    return 0;
}